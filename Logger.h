#pragma once
#include <ctime>
#include <fstream>
#include <iostream>

enum class MessageType { _INFO, _WARNING, _ERROR };

enum class OperationType {
  CREATE_FILE,
  CREATE_DIRECTORY,
  DELETE_FILE,
  DELETE_DIRECTORY,
};

class ILogger {
 public:
  virtual void log(const std::string& message, MessageType messageType) = 0;
  virtual ~ILogger() {}
};

class FileLogger : public ILogger {
 private:
  std::ofstream logFile;

 public:
  FileLogger(const std::string& filename);
  void log(const std::string& message, MessageType messageType) override;
};

class ConsoleLogger : public ILogger {
 public:
  void log(const std::string& message, MessageType messageType) override;
};

class Logger {
 private:
  ILogger& logger;

 public:
  Logger(ILogger& logger) : logger(logger) {}

  void logMessage(const std::string& message, MessageType messageType);
  void logFileOperation(const std::string& directoryPath,
                        OperationType operationType, bool success);
};
