#include <Windows.h>

#include "Menu.h"

Menu* Menu::_instance = nullptr;

int main() {
  setlocale(LC_ALL, "en_US.UTF-8");

  Menu* menu = Menu::Instance();
  menu->introPage();
  
  return 0;
}
