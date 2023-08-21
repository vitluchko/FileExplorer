#include "Logger.h"

std::string Logger::getCurrentTime() {
  currentTime = std::time(nullptr);
  localtime_s(&localTime, &currentTime);
  char buffer[80];
  std::strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S] ", &localTime);
  return std::string(buffer);
}

void Logger::noteAction(const std::string& message) {
  std::ofstream file("D://logs.txt", std::ios_base::app);
  if (file.is_open()) {
    file << getCurrentTime() << message << std::endl;
    file.close();
  }
}
