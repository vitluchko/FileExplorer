#pragma once
#include <ctime>
#include <fstream>
#include <iostream>

class Logger {
 private:
  std::time_t currentTime;
  std::tm localTime;

  std::string getCurrentTime();

 public:
  void noteAction(const std::string& message);
};
