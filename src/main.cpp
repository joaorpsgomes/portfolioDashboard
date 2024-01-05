#include "databaseWrapper.h"
#include "logger.h"
#include <memory>
#include <thread>
#include <chrono> // For std::chrono::seconds

int main() {
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    std::unique_ptr<logger> logger;
    std::unique_ptr<databaseWrapper> dbWrapper = std::make_unique<databaseWrapper>();
    return 0;
}
