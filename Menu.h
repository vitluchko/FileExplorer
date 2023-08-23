#pragma
#include <regex>
#include <string>

#include "FileManager.h"

class Menu {
 private:
  FileManager fm;
  std::string directoryPath;
  size_t i;

  void IstepAhead();
  void IstepBack();
  void IcreateFile();
  void IcreateDirectory();
  void IdeleteFileDirectory(const size_t index);

 public:
  void introPage();
  void mainPage();
};
