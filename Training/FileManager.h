#pragma once
#include <Windows.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "Logger.h"

namespace fs = std::filesystem;

class FileManager {
 private:
  DWORD drivesMask = GetLogicalDrives();  // ќтримуЇмо б≥товий шаблон диск≥в
  std::vector<std::string> fileList, driveList;
  Logger log;

 public:
  void getLocalDrives();
  void listDirectoryContents(const std::string& directoryPath);
  void deleteFile(const std::string& directoryPath);
  void deleteDirectory(const std::string& directoryPath);
  void createFile(const std::string& directoryPath);
  void createDirectory(const std::string& directoryPath);

  bool isValidIndex(const size_t i, const size_t flag);
  std::string setDirectory(const size_t i, const size_t flag);

  std::string stepAhead(const size_t index);
  std::string stepBack(const std::string& directoryPath);
};
