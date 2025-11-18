#ifndef CRYPTOGRAPHY1_LOGGER_H
#define CRYPTOGRAPHY1_LOGGER_H

#include <string>
#include "Types.h"
#include <cstdio>

/**
 * @brief A simple singleton logger class.
 *
 * This logger provides a simple way to log messages.
 * It supports formatted strings in a printf-like manner.
 */
class Logger {
public:
    /**
     * @brief Gets the singleton instance of the Logger.
     * @return A reference to the Logger instance.
     */
    static Logger& instance() {
        static Logger logger;
        return logger;
    }

    /**
     * @brief Logs a simple string message.
     *
     * @param msg The message to log.
     */
    void log(const String& msg) const;

    /**
     * @brief Prints a separator line to the console.
     *        This is useful for sectioning off different parts of the log output.
     */
    void print_separator() const;

    /**
     * @brief Prints a specified number of empty lines to the console.
     *        This can be used to add vertical spacing to the log output.
     * @param lines_to_print The number of empty lines to print. Defaults to 1.
     */
    void print_empty_line(int8 lines_to_print = 1) const;

    /**
     * @brief Logs a formatted string message.
     *
     * This function uses a printf-like format string and a variable number of
     * arguments.
     *
     * @tparam Args The types of the arguments.
     * @param format The format string.
     * @param args The arguments for the format string.
     */
    template<typename... Args>
    void log(const char* format, Args... args) const {
        int size = std::snprintf(nullptr, 0, format, args...);
        if (size < 0) {
            return;
        }

        Vector(char) buf(size + 1);
        std::snprintf(buf.data(), buf.size(), format, args...);

        log(String(buf.data()));
    }

private:
    /**
     * @brief Private constructor for the singleton pattern.
     */
    Logger();
};

#endif //CRYPTOGRAPHY1_LOGGER_H
