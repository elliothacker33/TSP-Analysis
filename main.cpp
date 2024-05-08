#include <iostream>
#include "src/controller/Manager.h"
#include "src/view/Menu.h"


int main() {
    auto* manager = new Manager();
    Menu* menu = new Menu(manager);
    menu->mainMenu();
    return 0;
}


