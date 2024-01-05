#ifndef DATABASEWRAPPER_H
#define DATABASEWRAPPER_H

#include "logger.h"
#include <cppconn/prepared_statement.h>
#include <mysql_driver.h>
#include <variant>

using tableEntries = std::variant<long double, int, std::string>;

class databaseWrapper {
public:
    enum Result { SUCCESS = 0, NO_CONNECTION = 1, COMMAND_ERROR = 2, BAD_USAGE=3 };

public:
    /**
     * @brief Constructor
     *
     * This method creates a connection to the portfolio schema
     */
    databaseWrapper();

    /**
     * @brief Destructor
     */
    ~databaseWrapper();

    /**
     * @brief Inserts a entry with fields in the table selected
     *
     * Example:
     * @code{.cpp}
     * std::map<std::string, tableEntries > entry;
     * entry.insert(std::pair<std::string, tableEntries>("Name", "test"));
     * entry.insert(std::pair<std::string, tableEntries>("Value", 2));
     * dbWrapper->insertInTable("Portefolio", entry);
     * @endcode
     *
     * @param table Table name
     * @param fields Map with the field name as the key and the value for the given field name as the map entry value
     *
     * @return Operation result:
     *          - SUCCESS If the operation was successfully
     *          - NO_CONNECTION If the connection is invalid
     *          - COMMAND_ERROR If the command is not formed correctly
     *
     */
    Result insertInTable(const std::string &table, const std::map<std::string, tableEntries> &fields);

    /**
     * @brief Returns a vector of table entries with the fields specified and the condition is meet
     *
     * Example:
     * @code{.cpp}
     * // Get the fields Name, Value and Type
     * std::vector<std::string> fields={"Name","Value","Type"};
     *
     * // Get all the entries which the Type is Crypto and the Name is BTC
     * std::map<std::string, tableEntries> condition = {{"type", "Crypto"}, {"Name", "BTC"}};
     *
     * // Variable to save the result
     * std::vector<std::map<std::string, tableEntries>> result;
     *
     * auto test = dbWrapper->getTableEntry("Portefolio", fields, result);
     * @endcode
     *
     * @param tableName Name of the table to retrieve the data
     * @param fields Fields to retrieve from the table. IF THE VECTOR IS EMPTY RETURN ALL FIELDS IN THE TABLE
     * @param condition Map of conditions to apply to data retrieval. The key should be the name of the column and the
     * value should be the value of the column. I.e. {"Type","crypto"}
     * @param result Result from the query in the following exampling format
     * @code
     * {
     *   {
     *      {"Name","AMZN"},
     *      {"Type","crypto"},
     *      {"Value", 12.23}
     *   },
     *   {
     *      {"Name","NVDA"},
     *      {"Type","stock"},
     *      {"Value", 1}
     *   }
     * }
     * @endcode
     * @return Operation result:
     *          - SUCCESS If the operation was successfully
     *          - NO_CONNECTION If the connection is invalid
     *          - COMMAND_ERROR If the command is not formed correctly
     */
    Result getTableEntry(std::string tableName, std::vector<std::string> fields,
                         std::map<std::string, tableEntries> &conditions,
                         std::vector<std::map<std::string, tableEntries>> &result);

    /**
     * @brief Returns a vector of table entries with the fields specified and the condition is meet, this will get all
     * the fields from the table
     *
     * Example:
     * @code{.cpp}
     * // Get the fields Name, Value and Type
     * std::vector<std::string> fields={"Name","Value","Type"};
     *
     * // Get all the entries which the Type is Crypto and the Name is BTC
     * std::map<std::string, tableEntries> condition = {{"type", "Crypto"}, {"Name", "BTC"}};
     *
     * // Variable to save the result
     * std::vector<std::map<std::string, tableEntries>> result;
     *
     * auto test = dbWrapper->getTableEntry("Portefolio", fields, result);
     * @endcode
     *
     * @param tableName Name of the table to retrieve the data
     * @param fields Fields to retrieve from the table. IF THE VECTOR IS EMPTY RETURN ALL FIELDS IN THE TABLE
     * @param result Result from the query in the following exampling format
     * @code
     * {
     *   {
     *      {"Name","AMZN"},
     *      {"Type","crypto"},
     *      {"Value", 12.23}
     *   },
     *   {
     *      {"Name","NVDA"},
     *      {"Type","stock"},
     *      {"Value", 1}
     *   }
     * }
     * @endcode
     *
     * @return Operation result:
     *          - SUCCESS If the operation was successfully
     *          - NO_CONNECTION If the connection is invalid
     *          - COMMAND_ERROR If the command is not formed correctly
     */
    Result getTableEntry(std::string tableName, std::vector<std::string> &fields,
                         std::vector<std::map<std::string, tableEntries>> &result);

    /**
     * @brief This method provides a way to update all the entries to a certain values
     *
     * @code
     * // All the entries with value 2
     * std::map<std::string, tableEntries> conditions={{"Value",2}};
     *
     * // Update the value to 3
     * std::map<std::string, tableEntries> values={{"Value",3}};
     *
     * // Update all the entries with the value=2 to value=3
     * dbWrapper->updateTableEntry("Portefolio",values,conditions);
     * @endcode
     *
     * @param tableName Name of the table to update the data
     * @param values The values to update in the table
     * @param conditions The conditions to discover which entries to update
     *
     * @return Operation result:
     *          - SUCCESS If the operation was successfully
     *          - BAD_USAGE If the function was not used correctly, values or conditions empty
     *          - NO_CONNECTION If the connection is invalid
     *          - COMMAND_ERROR If the command is not formed correctly
     */
    Result updateTableEntry(std::string tableName, std::map<std::string, tableEntries> &values,
                            std::map<std::string, tableEntries> &conditions);

    /**
     * @brief This method provides a way to update all the entries to a certain values
     *
     * @code
     * // Update the value to 3
     * std::map<std::string, tableEntries> values={{"Value",3}};
     *
     * // Update all the entries to value=3
     * dbWrapper->updateTableEntry("Portefolio",values,conditions);
     * @endcode
     *
     * @param tableName Name of the table to update the data
     * @param values The values to update in the table
     *
     * @return Operation result:
     *          - SUCCESS If the operation was successfully
     *          - BAD_USAGE If the function was not used correctly, values empty
     *          - NO_CONNECTION If the connection is invalid
     *          - COMMAND_ERROR If the command is not formed correctly
     */
    Result updateAllTableEntries(std::string tableName, std::map<std::string, tableEntries> &values);

    /**
     * @brief This method provides a way to delete entries from a table
     *
     * @code
     * // All the entries with Value=3
     * std::map<std::string, tableEntries> conditions={{"Value",2}};
     *
     * // Delete all the entries to Value=3
     * dbWrapper->deleteTableEntry("Portefolio",conditions);
     * @endcode
     *
     * @param tableName Name of the table to update the data
     * @param conditions The condition to discover which entries to delete
     *
     * @return Operation result:
     *          - SUCCESS If the operation was successfully
     *          - BAD_USAGE If the function was not used correctly, conditions empty
     *          - NO_CONNECTION If the connection is invalid
     *          - COMMAND_ERROR If the command is not formed correctly
     */
    Result deleteTableEntry(std::string tableName, std::map<std::string, tableEntries> &conditions);

    /**
     * @brief This method provides a way to clear a table
     *
     * @code
     * // Clear Portefolio table
     * dbWrapper->clearTable("Portefolio");
     * @endcode
     *
     * @param tableName Name of the table to update the data
     *
     * @return Operation result:
     *          - SUCCESS If the operation was successfully
     *          - NO_CONNECTION If the connection is invalid
     *          - COMMAND_ERROR If the command is not formed correctly
     */
    Result clearTable(std::string tableName);

private:
    sql::Connection *mCon;
    std::unique_ptr<logger> mLogger;
    sql::mysql::MySQL_Driver *mDriver;
};

#endif // DATABASEWRAPPER_H
