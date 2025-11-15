#include "Logger.h"
#include <cstdio>

Logger::Logger() {}

void Logger::log(const std::string& msg) const {
  std::printf("%s\n", msg.c_str());
}
