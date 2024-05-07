#include <iostream>
#include "src/controller/Manager.h"
#include "src/view/Menu.h"


int main() {
    auto* manager = new Manager(10);
    Menu* menu = new Menu(manager);
    menu->mainMenu();
    delete menu;
    return 0;
}


