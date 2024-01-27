#include "cryptoUpdater.h"
#include "databaseWrapper.h"
#include "logger.h"
#include <chrono> // For std::chrono::seconds
#include <memory>
#include <thread>

int main() {
    // std::this_thread::sleep_for(std::chrono::seconds(3));
    std::unique_ptr<logger> logger;
    std::unique_ptr<databaseWrapper> dbWrapper = std::make_unique<databaseWrapper>();

    std::unique_ptr<cryptoUpdater> updater = std::make_unique<cryptoUpdater>();

    updater->updateAssetsValue();
    return 0;
}
