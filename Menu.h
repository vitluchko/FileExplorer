#pragma
#include <regex>
#include <string>

#include "FileManager.h"

class Menu {
 private:
  static Menu* _instance;
  FileManager fm;
  std::string directoryPath;
  size_t i;

  void IstepAhead();
  void IstepBack();
  void IcreateFile();
  void IcreateDirectory();
  void IdeleteFileDirectory(const size_t index);

 protected:
  Menu() { i = 0; }

 public:
  void introPage();
  void mainPage();

  static Menu* Instance();
  ~Menu() { delete _instance; }
};
