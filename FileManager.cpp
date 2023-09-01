#include "FileManager.h"

void FileManager::getLocalDrives() {
  for (char driveLetter = 'A'; driveLetter <= 'Z'; ++driveLetter) {
    if (drivesMask & 1) {
      std::string drive = "";
      drive += driveLetter;
      drive += ":/";
      driveList.push_back(drive);
    }
    drivesMask >>= 1;
  }
  if (driveList.empty()) {
    consoleLoggerInstance.logMessage("No local drives found.",
                                     MessageType::_WARNING);
    fileLoggerInstance.logMessage("No local drives found.",
                                  MessageType::_WARNING);
  } else {
    consoleLoggerInstance.logMessage("List of local drives:",
                                     MessageType::_INFO);
    fileLoggerInstance.logMessage("List of local drivers was called.",
                                  MessageType::_INFO);
    for (size_t i = 0; i < driveList.size(); ++i) {
      std::cout << "[" << i + 1 << "] " << driveList[i] << std::endl;
    }
  }
}

void FileManager::listDirectoryContents(const std::string& directoryPath) {
  if (fs::exists(directoryPath) && fs::is_directory(directoryPath)) {
    fs::current_path(directoryPath);
    if (!fileList.empty()) {
      fileList.clear();
    }
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
      fileList.push_back(entry.path().filename().string());
    }
    consoleLoggerInstance.logMessage(
        "Contents of directory: " + directoryPath, MessageType::_INFO);
    fileLoggerInstance.logMessage(
        "Contents of directory " + directoryPath + " was called.",
        MessageType::_INFO);
    for (size_t i = 0; i < fileList.size(); ++i) {
      std::cout << "[" << i + 1 << "] " << fileList[i] << std::endl;
    }
  } else {
    consoleLoggerInstance.logMessage(
        "Directory does not exist or is not a directory.",
        MessageType::_WARNING);
    fileLoggerInstance.logMessage(
        "Directory does not exist or is not a directory.",
        MessageType::_WARNING);
  }
}

void FileManager::performFileOperation(const std::string& directoryPath,
                                       IFileOperations& operation,
                                       OperationType operationType) {
  try {
    operation.performOperation(directoryPath);
    fileLoggerInstance.logFileOperation(directoryPath, operationType, true);
  } catch (const std::exception& e) {
    fileLoggerInstance.logFileOperation(directoryPath + e.what(), operationType,
                                        false);
  }
}

std::string FileManager::stepAhead(const size_t index) {
  return (fileList[index - 1] + "/");
}

std::string FileManager::setDirectory(const size_t i) {
  return (driveList[i - 1].c_str());
}

bool FileManager::isValidIndex(const size_t i, const size_t flag) {
  if (flag == 0) {
    return ((i <= driveList.size()) && (i > 0));
  } else {
    return ((i <= fileList.size()) && (i > 0));
  }
}

std::string FileManager::stepBack(const std::string& directoryPath) {
  size_t slashPos = directoryPath.find_last_not_of('/');
  size_t beforePos = directoryPath.rfind('/', slashPos - 1);
  return std::string(directoryPath.substr(0, beforePos + 1));
}
