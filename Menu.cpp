#include "Menu.h"

Menu* Menu::Instance() {
  if (_instance == nullptr) {
    _instance = new Menu();
    return _instance;
  } else {
    return nullptr;
  }
}

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
    case 3:
      IcreateFile();
      break;
    case 4:
      IcreateDirectory();
      break;
    case 5:
      IdeleteFileDirectory(5);
      break;
    case 6:
      IdeleteFileDirectory(6);
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
  i = 0;
  if (directoryPath.size() == 3) {
    introPage();
  }
  directoryPath = fm.stepBack(directoryPath);
  std::cout << directoryPath << std::endl;
  mainPage();
}

void Menu::IcreateFile() {
  std::cout << "\033[2J\033[1;1H";
  fm.listDirectoryContents(directoryPath);
  std::cout << "\033[32m"
            << "Enter a filename with expansion:"
            << "\033[0m" << std::endl;
  std::string fileName;
  std::getline(std::cin, fileName);
  std::regex filenameRegex(R"([a-zA-Z0-9_-]+\.[a-zA-Z0-9]+)");
  if (std::regex_match(fileName, filenameRegex)) {
    fm.createFile(directoryPath + fileName);
    mainPage();
  } else {
    IcreateFile();
  }
}

void Menu::IcreateDirectory() {
  std::cout << "\033[2J\033[1;1H";
  fm.listDirectoryContents(directoryPath);
  std::cout << "\033[32m"
            << "Enter a directory name:"
            << "\033[0m" << std::endl;
  std::string directoryName;
  std::getline(std::cin, directoryName);
  std::regex directorynameRegex(R"([a-zA-Z0-9_-]+)");
  if (std::regex_match(directoryName, directorynameRegex)) {
    fm.createDirectory(directoryPath + directoryName);
    mainPage();
  } else {
    IcreateDirectory();
  }
}

void Menu::IdeleteFileDirectory(const size_t index) {
  std::cout << "\033[2J\033[1;1H";
  fm.listDirectoryContents(directoryPath);
  if (index == 5) {
    std::cout << "\033[32m"
              << "Enter a filename with expansion:"
              << "\033[0m" << std::endl;
  } else {
    std::cout << "\033[32m"
              << "Enter a directory name : "
              << "\033[0m" << std::endl;
  }
  std::string name;
  std::getline(std::cin, name);
  if (index == 5) {
    std::regex nameRegex(R"([a-zA-Z0-9_-]+\.[a-zA-Z0-9]+)");
    if (std::regex_match(name, nameRegex)) {
      fm.deleteFile(directoryPath + name);
      mainPage();
    } else {
      IdeleteFileDirectory(5);
    }
  } else {
    std::regex nameRegex(R"([a-zA-Z0-9_-]+)");
    if (std::regex_match(name, nameRegex)) {
      fm.deleteDirectory(directoryPath + name);
      mainPage();
    } else {
      IdeleteFileDirectory(6);
    }
  }
}
