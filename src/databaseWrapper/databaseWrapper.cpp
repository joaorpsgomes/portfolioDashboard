#include "databaseWrapper.h"
#include <memory>

databaseWrapper::databaseWrapper() {
    mLogger = std::make_unique<logger>();
    sql::mysql::MySQL_Driver *mDriver;
    try {
        mDriver = sql::mysql::get_mysql_driver_instance();
        const char *dockerEnv = std::getenv("DOCKER_NAME");
        if (dockerEnv != nullptr) {
            mCon = mDriver->connect("portfoliodashboard_database_1", "root", "root");
        } else {
            mCon = mDriver->connect("localhost", "root", "root");
        }

        mCon->setSchema("portfolio");
    } catch (sql::SQLException &e) {
        mLogger->logError("SQL Exception: %s", e.what());
    }
}

databaseWrapper::~databaseWrapper() { delete mCon; }

databaseWrapper::Result databaseWrapper::insertInTable(const std::string &table,
                                                       const std::map<std::string, tableEntries> &fields) {

    if (!mCon->isValid()) {
        return Result::NO_CONNECTION;
    }
    std::string command = "INSERT INTO " + table + " (";
    std::string insertValues = " VALUES (";
    bool flag = false;

    for (const auto &columnValuePair : fields) {
        if (flag) {
            insertValues += ",";
            command += ",";
        }
        flag = true;

        command += columnValuePair.first;
        if (std::holds_alternative<int>(columnValuePair.second)) {
            insertValues += std::to_string(std::get<int>(columnValuePair.second));
        } else if (std::holds_alternative<std::string>(columnValuePair.second)) {
            insertValues += "\"" + std::get<std::string>(columnValuePair.second) + "\"";
        }
    }
    command += ")" + insertValues + ")";

    mLogger->logInfo(command.c_str());
    try {
        sql::PreparedStatement *pstmt;
        pstmt = mCon->prepareStatement(command);
        pstmt->executeUpdate();
    } catch (sql::SQLException &e) {
        mLogger->logError("SQL exception: %s\nCould not insert in table", e.what());
        return Result::COMMAND_ERROR;
    }
    mLogger->logInfo("Entry Added");
    return Result::SUCCESS;
}

databaseWrapper::Result databaseWrapper::getTableEntry(std::string tableName, std::vector<std::string> fields,
                                                       std::map<std::string, tableEntries> &conditions,
                                                       std::vector<std::map<std::string, tableEntries>> &result) {
    if (!mCon->isValid()) {
        return Result::NO_CONNECTION;
    }

    std::string command = "SELECT ";
    bool flag = false;

    // Check the fields to retrieve from the database
    if (fields.size() == 0) {
        // If the fields is empty then we want all the fields
        command += "*";
    } else {
        // Add all the fields in the vector to the command
        for (const auto &field : fields) {
            if (flag) {
                command += ", ";
            }
            flag = true;
            command += field;
        }
    }
    flag = false;

    // Add the table name
    command += " FROM " + tableName + " ";

    if (conditions.size() > 0) {
        std::string subCommand = "WHERE ";
        for (const auto &condition : conditions) {
            if (flag) {
                subCommand += " AND ";
            }
            flag = true;
            subCommand += condition.first + " = ";
            if (std::holds_alternative<int>(condition.second)) {
                subCommand += std::get<int>(condition.second);
            } else if (std::holds_alternative<std::string>(condition.second)) {
                subCommand += "\'" + std::get<std::string>(condition.second) + "\'";
            }
        }
        command += subCommand + ";";
    }

    // Execute the command
    try {
        sql::Statement *stmt = mCon->createStatement();
        sql::ResultSet *res = stmt->executeQuery(command);
        sql::ResultSetMetaData *metaData = res->getMetaData();
        int columnCount = metaData->getColumnCount();
        std::vector<std::string> collumnsNames;

        // Iterate for each row from the result of the command
        while (res->next()) {
            std::map<std::string, tableEntries> entry;
            // Iterate for each of the table row value
            for (int i = 1; i <= columnCount; ++i) {
                const auto columnType = metaData->getColumnTypeName(i);
                const auto columnName = metaData->getColumnName(i);

                // Check the type of the value and save it
                if (columnType == "VARCHAR" || columnType == "CHAR" || columnType == "TEXT") {
                    entry[columnName] = res->getString(i);
                    // Handle string value
                } else if (columnType == "INT" || columnType == "INTEGER") {
                    entry[columnName] = res->getInt(i);
                    // Handle integer value
                } else if (columnType == "DOUBLE") {
                    entry[columnName] = res->getDouble(i);
                    // Handle double value
                } else {
                    // Handle other data types as needed
                    std::cout << "Unknown type for column " << columnName << std::endl;
                }
            }
            // Save the row in the result vector
            result.push_back(entry);
            entry.clear();
        }
        delete stmt;
        delete res;
    } catch (sql::SQLException &e) {
        mLogger->logError("SQL exception: %s\nCould not retrieve table entry", e.what());
        return Result::COMMAND_ERROR;
    }

    return Result::SUCCESS;
}

databaseWrapper::Result databaseWrapper::getTableEntry(std::string tableName, std::vector<std::string> &fields,
                                                       std::vector<std::map<std::string, tableEntries>> &result) {
    auto conditions = std::map<std::string, tableEntries>();
    return getTableEntry(tableName, fields, conditions, result);
}

databaseWrapper::Result databaseWrapper::updateTableEntry(std::string tableName,
                                                          std::map<std::string, tableEntries> &values,
                                                          std::map<std::string, tableEntries> &conditions) {
    if (!mCon->isValid()) {
        return Result::NO_CONNECTION;
    }

    if (conditions.size() == 0) {
        mLogger->logWarn("Cannot call updateTableEntry with no conditions");
        return Result::BAD_USAGE;
    }

    if (values.size() == 0) {
        mLogger->logWarn("Cannot call updateTableEntry with no values to use in the update");
        return Result::BAD_USAGE;
    }

    std::string command = "UPDATE " + tableName + " SET ";
    bool flag = false;

    for (const auto &value : values) {
        if (flag) {
            command += ", ";
        }
        flag = true;

        command += value.first + " = ";

        if (std::holds_alternative<int>(value.second)) {
            command += std::to_string(std::get<int>(value.second));
        } else if (std::holds_alternative<std::string>(value.second)) {
            command += "\"" + std::get<std::string>(value.second) + "\"";
        }
    }

    command += " WHERE ";
    flag = false;
    for (const auto &condition : conditions) {
        if (flag) {
            command += ", ";
        }
        flag = true;

        command += condition.first + " = ";

        if (std::holds_alternative<int>(condition.second)) {
            command += std::to_string(std::get<int>(condition.second));
        } else if (std::holds_alternative<std::string>(condition.second)) {
            command += "\"" + std::get<std::string>(condition.second) + "\"";
        }
    }

    try {
        // Create a statement object
        sql::Statement *stmt = mCon->createStatement();
        // Execute the update query
        stmt->execute(command);
        delete stmt;
    } catch (sql::SQLException &e) {
        mLogger->logError("SQL exception: %s\nCould not update the table", e.what());
        return Result::COMMAND_ERROR;
    }
    return Result::SUCCESS;
}

databaseWrapper::Result databaseWrapper::updateAllTableEntries(std::string tableName,
                                                               std::map<std::string, tableEntries> &values) {

    if (!mCon->isValid()) {
        return Result::NO_CONNECTION;
    }

    if (values.size() == 0) {
        mLogger->logWarn("Cannot call updateTableEntry with no values to use in the update");
        return Result::BAD_USAGE;
    }

    std::string command = "UPDATE " + tableName + " SET ";
    bool flag = false;

    for (const auto &value : values) {
        if (flag) {
            command += ", ";
        }
        flag = true;

        command += value.first + " = ";

        if (std::holds_alternative<int>(value.second)) {
            command += std::to_string(std::get<int>(value.second));
        } else if (std::holds_alternative<std::string>(value.second)) {
            command += "\"" + std::get<std::string>(value.second) + "\"";
        }
    }
    try {
        // Create a statement object
        sql::Statement *stmt = mCon->createStatement();
        // Execute the update query
        stmt->execute(command);
        delete stmt;
    } catch (sql::SQLException &e) {
        mLogger->logError("SQL exception: %s\nCould not update the table", e.what());
        return Result::COMMAND_ERROR;
    }

    return Result::SUCCESS;
}

databaseWrapper::Result databaseWrapper::deleteTableEntry(std::string tableName,
                                                          std::map<std::string, tableEntries> &conditions) {
    if (!mCon->isValid()) {
        return Result::NO_CONNECTION;
    }

    if (conditions.size() == 0) {
        mLogger->logWarn("Cannot call deleteTableEntry with no conditions");
        return Result::BAD_USAGE;
    }

    std::string command="DELETE FROM "+tableName+" WHERE ";
    bool flag=false;

    for (const auto& condition : conditions) {
        if (flag) {
            command+=", ";
        }
        flag = true;

        command+=condition.first+" = ";
        if (std::holds_alternative<int>(condition.second)) {
            command += std::to_string(std::get<int>(condition.second));
        } else if (std::holds_alternative<std::string>(condition.second)) {
            command += "\"" + std::get<std::string>(condition.second) + "\"";
        }
    }
    try {
        // Create a statement object
        sql::Statement *stmt = mCon->createStatement();
        // Execute the update query
        stmt->execute(command);
        delete stmt;
    } catch (sql::SQLException &e) {
        mLogger->logError("SQL exception: %s\nCould not delete from table", e.what());
        return Result::COMMAND_ERROR;
    }

    return Result::SUCCESS;
}

databaseWrapper::Result databaseWrapper::clearTable(std::string tableName) {
    if (!mCon->isValid()) {
        return Result::NO_CONNECTION;
    }

    std::string command="DELETE FROM "+tableName;
    bool flag=false;

    try {
        // Create a statement object
        sql::Statement *stmt = mCon->createStatement();
        // Execute the update query
        stmt->execute(command);
        delete stmt;
    } catch (sql::SQLException &e) {
        mLogger->logError("SQL exception: %s\nCould not delete table", e.what());
        return Result::COMMAND_ERROR;
    }

    return Result::SUCCESS;
}
