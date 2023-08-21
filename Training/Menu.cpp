#include "Menu.h"

void Menu::introPage() {
  while (!fm.isValidIndex(i, 0)) {
    std::cout << "\033[2J\033[1;1H";
    fm.getLocalDrives();
    std::cout << "\033[32m"
              << "Choose the disk directory:"
              << "\033[0m" << std::endl;
    if (!directoryPath.empty()) {
      directoryPath.clear();
    }
    std::cin >> i;
  }
  directoryPath = fm.setDirectory(i);
  i = 0;
  mainPage();
}

void Menu::mainPage() {
  std::cout << "\033[2J\033[1;1H";
  fm.listDirectoryContents(directoryPath);

  std::cout << "\033[93m"
            << "[1] Step ahead" << std::endl;
  std::cout << "[2] Step back" << std::endl;
  std::cout << "[3] Create file" << std::endl;
  std::cout << "[4] Create directory" << std::endl;
  std::cout << "[5] Delete file" << std::endl;
  std::cout << "[6] Delete directory" << std::endl;
  std::cout << "[7] Change disk"
            << "\033[0m" << std::endl;
  std::cout << "\033[32m"
            << "Choose the action:"
            << "\033[0m" << std::endl;

  std::cin >> i;

  switch (i) {
    case 1:
      IstepAhead();
      break;
    case 2:
      IstepBack();
      break;
    case 7:
      introPage();
      break;
    default:
      mainPage();
  }
}

void Menu::IstepAhead() {
  i = 0;
  while (!fm.isValidIndex(i, 1)) {
    std::cout << "\033[2J\033[1;1H";
    fm.listDirectoryContents(directoryPath);
    std::cout << "\033[32m"
              << "Choose the file directory:"
              << "\033[0m" << std::endl;
    std::cin >> i;
  }
  std::cout << fm.stepAhead(i) << std::endl;
  directoryPath += fm.stepAhead(i);
  i = 0;
  mainPage();
}

void Menu::IstepBack() {
  directoryPath = fm.stepBack(directoryPath);
  std::cout << directoryPath << std::endl;
  mainPage();
}
