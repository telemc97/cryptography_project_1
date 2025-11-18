#include "Logger.h"
#include <cstdio>

Logger::Logger() {}

void Logger::log(const std::string& msg) const {
  std::printf("%s\n", msg.c_str());
}

void Logger::print_separator() const {
    log("--------------------------------------------------");
}

void Logger::print_empty_line(int8 lines_to_print) const {
    for (int i = 0; i < lines_to_print; ++i) {
        log("");
    }
}
