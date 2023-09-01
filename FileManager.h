#pragma once

#include "FileOperations.h"

class FileManager {
 private:
  DWORD drivesMask = GetLogicalDrives();  // ќтримуЇмо б≥товий шаблон диск≥в
  std::vector<std::string> fileList, driveList;

 public:
  void getLocalDrives();
  void listDirectoryContents(const std::string& directoryPath);

  void performFileOperation(const std::string& directoryPath,
                            IFileOperations& operation, OperationType operationType);

  bool isValidIndex(const size_t i, const size_t flag);
  std::string setDirectory(const size_t i);

  std::string stepAhead(const size_t index);
  std::string stepBack(const std::string& directoryPath);
};
