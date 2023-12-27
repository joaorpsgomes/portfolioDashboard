#include "logger.h"

logger::logger() {
    int ret = sd_journal_open(&mJournal, SD_JOURNAL_LOCAL_ONLY);
    if (ret < 0) {
        return;
    }

    sd_journal_send("MESSAGE=%s", "Journal initialized", "PRIORITY=%i",
                    LOG_INFO, NULL);
    return;
}

logger::~logger(){
    sd_journal_close(mJournal);
}

void logger::logInfo(const char *format, ...) {
    std::va_list args;
    va_start(args, format);

    char buffer[2048]; // A buffer to store the formatted string
    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);
    sd_journal_send("MESSAGE=%s", buffer, "PRIORITY=%i", LOG_INFO, NULL);
#ifndef NDEBUG
    std::cout << GREEN_COLOR << "[INFO ]" << buffer << RESET_COLOR << std::endl;
#endif
    return;
}

void logger::logWarn(const char *format, ...) {
    std::va_list args;
    va_start(args, format);

    char buffer[2048]; // A buffer to store the formatted string
    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);
    sd_journal_send("MESSAGE=%s", buffer, "PRIORITY=%i", LOG_WARNING, NULL);
#ifndef NDEBUG
    std::cout << YELLOW_COLOR << "[WARN ]" << buffer << RESET_COLOR << std::endl;
#endif
    return;
}

void logger::logError(const char *format, ...) {
    std::va_list args;
    va_start(args, format);

    char buffer[2048]; // A buffer to store the formatted string
    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);
    sd_journal_send("MESSAGE=%s", buffer, "PRIORITY=%i", LOG_ERR, NULL);
#ifndef NDEBUG
    std::cout << RED_COLOR << "[ERROR]" << buffer << RESET_COLOR << std::endl;
#endif
    return;
}

void logger::logDebug(const char *format, ...) {
    std::va_list args;
    va_start(args, format);

    char buffer[2048]; // A buffer to store the formatted string
    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);
#ifndef NDEBUG
    std::cout << "[DEBUG]" << buffer << std::endl;
#endif
    return;
}