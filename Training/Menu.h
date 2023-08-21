#pragma
#include "FileManager.h"
class Menu {
 private:
  FileManager fm;
  std::string directoryPath;
  size_t i;

  void IstepAhead();
  void IstepBack();

 public:
  void introPage();
  void mainPage();
};
