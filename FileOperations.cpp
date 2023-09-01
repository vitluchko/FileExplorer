#include "FileOperations.h"
void FileDeleter::performOperation(const std::string& directoryPath) {
  if (fs::exists(directoryPath)) {
    try {
      if (fs::is_regular_file(directoryPath)) {
        fs::remove(directoryPath);
        consoleLoggerInstance.logMessage(
            "File " + directoryPath + " deleted successfully.",
            MessageType::_INFO);
        fileLoggerInstance.logMessage(
            "File " + directoryPath + " deleted successfully.",
            MessageType::_INFO);
      }
    } catch (const fs::filesystem_error& e) {
      consoleLoggerInstance.logMessage(
          "Error deleting " + directoryPath + ": " + e.what(),
          MessageType::_ERROR);
      fileLoggerInstance.logMessage(
          "Error deleting " + directoryPath + ": " + e.what(),
          MessageType::_ERROR);
    }
  } else {
    consoleLoggerInstance.logMessage("File does not exist.",
                                     MessageType::_WARNING);
    fileLoggerInstance.logMessage("File does not exist.",
                                  MessageType::_WARNING);
  }
}

void FileCreator::performOperation(const std::string& directoryPath) {
  std::ofstream file(directoryPath);
  if (file.is_open()) {
    consoleLoggerInstance.logMessage(
        "File " + directoryPath + " created successfully.", MessageType::_INFO);
    fileLoggerInstance.logMessage(
        "File " + directoryPath + " created successfully.", MessageType::_INFO);
    file.close();
  } else {
    consoleLoggerInstance.logMessage("Error creating file " + directoryPath,
                                     MessageType::_ERROR);
    fileLoggerInstance.logMessage("Error creating file " + directoryPath,
                                  MessageType::_ERROR);
  }
}

void DirectoryDeleter::performOperation(const std::string& directoryPath) {
  if (fs::exists(directoryPath)) {
    try {
      if (fs::is_directory(directoryPath)) {
        fs::remove_all(directoryPath);
        consoleLoggerInstance.logMessage(
            "Directory " + directoryPath + " deleted successfully.",
            MessageType::_INFO);
        fileLoggerInstance.logMessage(
            "Directory " + directoryPath + " deleted successfully.",
            MessageType::_INFO);
      }
    } catch (const fs::filesystem_error& e) {
      consoleLoggerInstance.logMessage(
          "Error deleting " + directoryPath + ": " + e.what(),
          MessageType::_ERROR);
      fileLoggerInstance.logMessage(
          "Error deleting " + directoryPath + ": " + e.what(),
          MessageType::_ERROR);
    }
  } else {
    consoleLoggerInstance.logMessage("Directory does not exist.",
                                     MessageType::_WARNING);
    fileLoggerInstance.logMessage("Directory does not exist.",
                                  MessageType::_WARNING);
  }
}

void DirectoryCreator::performOperation(const std::string& directoryPath) {
  if (fs::create_directory(directoryPath)) {
    consoleLoggerInstance.logMessage(
        "Directory " + directoryPath + " created successfully.",
        MessageType::_INFO);
    fileLoggerInstance.logMessage(
        "Directory " + directoryPath + " created successfully.",
        MessageType::_INFO);
  } else {
    consoleLoggerInstance.logMessage(
        "Error creating directory " + directoryPath, MessageType::_ERROR);
    fileLoggerInstance.logMessage("Error creating directory " + directoryPath,
                                  MessageType::_ERROR);
  }
}