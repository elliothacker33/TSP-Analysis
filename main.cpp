#include <iostream>
#include "src/controller/Manager.h"
#include "src/view/Menu.h"


int main() {
    try {
        auto *manager = new Manager();
        Menu *menu = new Menu(manager);
        menu->mainMenu();
    }
    catch (const CustomError& e) {
        e.what();
        exit(EXIT_FAILURE);
    }
    catch(...){
        exit(EXIT_FAILURE);
    }
    return 0;
}


