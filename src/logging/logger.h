/**
 * @file logger.h
 * @brief Provides logging interface
 */
#ifndef LOGGER_H
#define LOGGER_H

#ifndef NDEBUG

#include <iostream>

#endif

#include <cstdarg>
#include <string>
#include <systemd/sd-journal.h>

/// Logger color reset for standard output
#define RESET_COLOR "\033[0m"
/// Logger set color to red for standard output
#define RED_COLOR "\033[31m"
/// Logger set color to yellow for standard output
#define YELLOW_COLOR "\033[33m"
/// Logger set color to green for standard output
#define GREEN_COLOR "\033[32m"

/**
 * @brief This class creates a logging interface to the standard output as well
 * as to the journal
 */
class logger {

  public:
    /**
     * @brief Logger constructor
     *
     * Creates a journal logger instance and logs the logger initialization
     */
    logger();

    ~logger();

    /**
     * @brief Logs a message of Info type to the standard output as well as to
     * the journal
     *
     * @param format Message in a string format similar to the printf function
     * @param ... Values to insert on the message
     */
    void logInfo(const char *format, ...);

    /**
     * @brief Logs a message of Warning type to the standard output as well as
     * to the journal
     *
     * @param format Message in a string format similar to the printf function
     * @param ... Values to insert on the message
     */
    void logWarn(const char *format, ...);

    /**
     * @brief Logs a message of Error type to the standard output as well as to
     * the journal
     *
     * @param format Message in a string format similar to the printf function
     * @param ... Values to insert on the message
     */
    void logError(const char *format, ...);

    /**
     * @brief Logs a message of Debug type only to the standard output
     *
     * @param format Message in a string format similar to the printf function
     * @param ... Values to insert on the message
     */
    void logDebug(const char *format, ...);

  private:
    sd_journal *mJournal;
};

#endif // LOGGER_H
