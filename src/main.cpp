#include "databaseWrapper.h"
#include "logger.h"
#include <memory>
#include <thread>
#include <chrono> // For std::chrono::seconds

int main() {
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    std::unique_ptr<logger> logger;
    std::unique_ptr<databaseWrapper> dbWrapper = std::make_unique<databaseWrapper>();
    logger->logWarn("Hello %d", 2);
    // Test insert command
    std::map<std::string, tableEntries > entry;
    entry.insert(std::pair<std::string, tableEntries>("Name", "test"));
        entry.insert(std::pair<std::string, tableEntries>("Value", 2));
    dbWrapper->insertInTable("Portefolio", entry);

    // Test get command
     std::vector<std::string> fields={"Name","Value","Type"};
    //std::vector<std::string> fields;
    //std::map<std::string, tableEntries> condition = {{"type", "Crypto"}, {"Name", "BTC"}};
    std::map<std::string, tableEntries> condition;
    std::vector<std::map<std::string, tableEntries>> result;
    auto test = dbWrapper->getTableEntry("Portefolio", fields, result);

    std::map<std::string, tableEntries> values={{"Value",3}};
    std::map<std::string, tableEntries> conditions={{"Value",2}};
    dbWrapper->updateTableEntry("Portefolio",values,conditions);
    //std::map<std::string,tableEntries> conditions= {{"Name", "test"}};
    dbWrapper->deleteTableEntry("Portefolio",conditions);
    logger->logInfo("Hello world");
    return 0;
}
