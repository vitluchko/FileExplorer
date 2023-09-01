#pragma once
#include <Windows.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "Logger.h"

namespace fs = std::filesystem;

static FileLogger fileLogger("D://log.txt");
static ConsoleLogger consoleLogger;
static Logger fileLoggerInstance(fileLogger), consoleLoggerInstance(consoleLogger);

class IFileOperations {
 public:
  virtual void performOperation(const std::string& directoryPath) = 0;
};

class FileDeleter : public IFileOperations {
 public:
  void performOperation(const std::string& directoryPath) override;
};

class FileCreator : public IFileOperations {
 public:
  void performOperation(const std::string& directoryPath) override;
};

class DirectoryDeleter : public IFileOperations {
 public:
  void performOperation(const std::string& directoryPath) override;
};

class DirectoryCreator : public IFileOperations {
 public:
  void performOperation(const std::string& directoryPath) override;
};