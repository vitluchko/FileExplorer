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
    std::cout << "No local drives found." << std::endl;
    log.noteAction("No local drives found.");
  } else {
    log.noteAction("List of local drivers was called.");
    std::cout << "List of local drives:" << std::endl;
    for (size_t i = 0; i < driveList.size(); ++i) {
      std::cout << "[" << i + 1 << "] " << driveList[i] << std::endl;
    }
  }
}

void FileManager::listDirectoryContents(const std::string& directoryPath) {
  std::cout << directoryPath << std::endl;
  if (fs::exists(directoryPath) && fs::is_directory(directoryPath)) {
    fs::current_path(directoryPath);
    if (!fileList.empty()) {
      fileList.clear();
    }
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
      fileList.push_back(entry.path().filename().string());
    }
    log.noteAction("Contents of directory " + directoryPath + " was called.");
    std::cout << "Contents of directory: " << directoryPath << std::endl;
    for (size_t i = 0; i < fileList.size(); ++i) {
      std::cout << "[" << i + 1 << "] " << fileList[i] << std::endl;
    }
  } else {
    std::cout << "Directory does not exist or is not a directory." << std::endl;
    log.noteAction("Directory does not exist or is not a directory.");
  }
}

void FileManager::deleteFile(const std::string& directoryPath) {
  if (fs::exists(directoryPath)) {
    try {
      if (fs::is_regular_file(directoryPath)) {
        fs::remove(directoryPath);
        std::cout << "File " << directoryPath << " deleted successfully."
                  << std::endl;
        log.noteAction("File " + directoryPath + " deleted successfully.");
      }
    } catch (const fs::filesystem_error& e) {
      std::cerr << "Error deleting " << directoryPath << ": " << e.what()
                << std::endl;
      log.noteAction("Error deleting " + directoryPath + ": " + e.what());
    }
  } else {
    std::cout << "File does not exist." << std::endl;
    log.noteAction("File does not exist.");
  }
}

void FileManager::deleteDirectory(const std::string& directoryPath) {
  if (fs::exists(directoryPath)) {
    try {
      if (fs::is_directory(directoryPath)) {
        fs::remove_all(directoryPath);
        std::cout << "Directory " << directoryPath << " deleted successfully."
                  << std::endl;
        log.noteAction("Directory " + directoryPath + " deleted successfully.");
      }
    } catch (const fs::filesystem_error& e) {
      std::cerr << "Error deleting " << directoryPath << ": " << e.what()
                << std::endl;
      log.noteAction("Error deleting " + directoryPath + ": " + e.what());
    }
  } else {
    std::cout << "Directory does not exist." << std::endl;
    log.noteAction("Directory does not exist.");
  }
}

void FileManager::createFile(const std::string& directoryPath) {
  std::ofstream file(directoryPath);
  if (file.is_open()) {
    log.noteAction("File " + directoryPath + " created successfully.");
    std::cout << "File " << directoryPath << " created successfully."
              << std::endl;
    file.close();
  } else {
    std::cerr << "Error creating file " << directoryPath << std::endl;
    log.noteAction("Error creating file " + directoryPath);
  }
}

void FileManager::createDirectory(const std::string& directoryPath) {
  if (fs::create_directory(directoryPath)) {
    log.noteAction("Directory " + directoryPath + " created successfully.");
    std::cout << "Directory " << directoryPath << " created successfully."
              << std::endl;
  } else {
    std::cerr << "Error creating directory " << directoryPath << std::endl;
    log.noteAction("Error creating directory " + directoryPath);
  }
}

std::string FileManager::stepAhead(const size_t index) {
  return (fileList[index - 1] + "/");
}

std::string FileManager::setDirectory(const size_t i, const size_t flag) {
  if (flag == 0) {
    return (driveList[i - 1].c_str());
  } else {
    return (fileList[i - 1].c_str());
  }
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
