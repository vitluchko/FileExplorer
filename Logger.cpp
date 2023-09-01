#include "Logger.h"

FileLogger::FileLogger(const std::string& filename) {
  logFile.open(filename, std::ios::app);
}

void FileLogger::log(const std::string& message, MessageType messageType) {
  std::string typePrefix;
  switch (messageType) {
    case MessageType::_INFO:
      typePrefix = "[INFO] ";
      break;
    case MessageType::_WARNING:
      typePrefix = "[WARNING] ";
      break;
    case MessageType::_ERROR:
      typePrefix = "[ERROR] ";
      break;
    default:
      typePrefix = "[UNKNOWN] ";
      break;
  }

  std::tm localTime;
  std::time_t currentTime = std::time(nullptr);
  localtime_s(&localTime, &currentTime);
  char buffer[80];
  std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);

  std::string logEntry =
      "[" + std::string(buffer) + "] " + typePrefix + message;

  logFile << logEntry << std::endl;
}

void ConsoleLogger::log(const std::string& message, MessageType messageType) {
  switch (messageType) {
    case MessageType::_INFO:
      std::cout << "\033[32m[INFO] ";
      break;
    case MessageType::_WARNING:
      std::cout << "\033[33m[WARNING] ";
      break;
    case MessageType::_ERROR:
      std::cout << "\033[31m[ERROR] ";
      break;
    default:
      std::cout << "[UNKNOWN] ";
      break;
  }

  std::cout << message << "\033[0m" << std::endl;
}

void Logger::logMessage(const std::string& message, MessageType messageType) {
  // Delegate the log message to the provided logger
  logger.log(message, messageType);
}

void Logger::logFileOperation(const std::string& directoryPath,
                              OperationType operationType, bool success) {
  std::string operationTypeStr;
  switch (operationType) {
    case OperationType::CREATE_FILE:
      operationTypeStr = "Create File";
      break;
    case OperationType::CREATE_DIRECTORY:
      operationTypeStr = "Create Directory";
      break;
    case OperationType::DELETE_FILE:
      operationTypeStr = "Delete File";
      break;
    case OperationType::DELETE_DIRECTORY:
      operationTypeStr = "Delete Directory";
      break;
    default:
      operationTypeStr = "Unknown Operation";
      break;
  }

  if (success) {
    logger.log("File operation successful: " + operationTypeStr + " - " +
                   directoryPath,
               MessageType::_INFO);
  } else {
    logger.log(
        "File operation failed: " + operationTypeStr + " - " + directoryPath,
        MessageType::_ERROR);
  }
}
