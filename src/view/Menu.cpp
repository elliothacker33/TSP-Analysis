/**
 *
* @file Menu.cpp
* @brief This file contains the Menu implementation.
*/
// Project headers
#include "Menu.h"
// Standard Library Headers
#include <sstream>

Menu::~Menu() {
    delete manager;
}

Menu::Menu(Manager* manager) {
    try {
        if (manager == nullptr) {
            throw CustomError("NullPtr: Manager is a null ptr", ERROR);
        }
        this->manager = manager;
        this->mode = false; // Default mode : Real World
    }
    catch (const CustomError& e){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

/* Auxiliary functions */
string Menu::removeLeadingTrailingSpaces(const string& input) {
    const auto start = input.find_first_not_of(" \n\r\t");
    const auto end = input.find_last_not_of(" \n\r\t");

    return (start != string::npos && end != string::npos) ? input.substr(start, end - start + 1) : "";
}

/* Get Input functions */

bool Menu::getNumberInput(int* option, int maxInput,int minInput) {
    try {
        cout << "Enter your choice (" << 1 << "-" << maxInput << "): ";
        string s_input;
        getline(cin, s_input);
        stringstream ss(s_input);
        int input;
        ss >> input;

        string trimmedInput = removeLeadingTrailingSpaces(s_input);

        if (trimmedInput.size() == 1 && input >= minInput && input <= maxInput) {
            *option = input;
            return true;
        }

        cout << "Invalid input. Please enter a number between " << 1 << " and " << maxInput << endl;
        return false;
    }
    catch (const CustomError& e){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

/* Get vertex examples */

void Menu::chooseVertex(int &vertex_id) {
    try {
        string input;
        HashTable *table = manager->getVerticesTable();

        while (true) {
            getVertexExamples();
            cout << "Enter a valid vertex id, press 'DEFAULT' for default, or press 'STOP' to stop inserting: " << endl;
            getline(cin, input);
            input = removeLeadingTrailingSpaces(input);

            if (input == "STOP") {
                vertex_id = -1;
                return;
            } else if (input == "DEFAULT") {
                vertex_id = 0;
                return;
            } else {
                try {
                    vertex_id = stoi(input);
                    if (table->search(vertex_id) != nullptr) {
                        return;
                    } else {
                        cout << "The entered vertex id is not present in the table." << endl;
                    }
                } catch (const std::invalid_argument &e) {
                    throw CustomError("Semantic error: string not convertable to int", SEMANTIC_ERROR);
                }
            }
        }
    }
    catch (const CustomError& e ){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

void Menu::getVertexExamples(){
    try {
        HashTable *table = manager->getVerticesTable();
        if (table == nullptr) {
            throw CustomError("NullPtr: table is a null ptr", ERROR);
        }
        // If more than 3 vertices, show 3 for example else show all.
        if (table->getSize() >= 3) {
            int count = 0;
            for (Vertex *v: manager->getGraph()->getVertexSet()) {
                if (v == nullptr) {
                    throw CustomError("NullPtr: v is a null ptr", ERROR);
                }
                if (count == 3) {
                    break;
                }
                cout << "Vertex with label and id (use id): " << v->getLabel() << ", " << v->getId() << endl;
                count++;
            }
        } else {
            for (Vertex *v: manager->getGraph()->getVertexSet()) {
                if (v == nullptr) {
                    throw CustomError("NullPtr: v is a null ptr", ERROR);
                }
                cout << "Vertex with label and id (use id): " << v->getLabel() << ", " << v->getId() << endl;
            }
        }

    }
    catch (const CustomError& e){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

/** Results functions **/

void Menu::displayResult(const Result& r){
    try {
        if (r.tour.empty()) {
            cout << "No solution was found" << endl;
        }
        else {
            for (Edge *e: r.tour) {
                if (e == nullptr) {
                    throw CustomError("NullPtr: edge e is null ptr", ERROR);
                }
                cout << e->getOrigin()->getLabel() << "-> " << e->getDestination()->getLabel() << endl;
            }

            cout << "Distance: " << r.distance << endl;
            cout << "CPU Time: " << r.time_spent.elapsed_cpu << " Real Time: " << r.time_spent.elapsed_real << endl;
        }
    }
    catch (const CustomError& e){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }

}
/** Menus **/

void Menu::mainMenu() {
    try {
        int option = 0;
        do {
            cout << "------------------------------------------------" << endl;
            cout << "            Menu -> Main menu                   " << endl;
            cout << "                                                " << endl;
            cout << "             1. Symmetric mode                  " << endl;
            cout << "             2. Real mode                       " << endl;
            cout << "             3. Exit menu                       " << endl;
            cout << "                                                " << endl;
            cout << "------------------------------------------------" << endl;
        } while (!getNumberInput(&option, 3, 1));

        switch (option) {
            case 1:
                this->mode = true;
                menuStack.push(&Menu::mainMenu);
                dataSetMenu();
                break;
            case 2:
                this->mode = false;
                menuStack.push(&Menu::mainMenu);
                dataSetMenu();
                break;
            case 3:
                exitMenu();
                break;
            default:
                throw CustomError("Menu not found", MENU_ERROR);
        }
    }
    catch(const CustomError& e){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

void Menu::dataSetMenu() {
    try {
        int option = 0;
        do {
            cout << "------------------------------------------------" << endl;
            cout << "                Menu -> Data set menu           " << endl;
            cout << "                                                " << endl;
            cout << "             1. Choose toy data set             " << endl;
            cout << "             2. Choose medium data set          " << endl;
            cout << "             3. Choose Real-World data set      " << endl;
            cout << "             4. Choose your own data set        " << endl;
            cout << "             5. Go back                         " << endl;
            cout << "                                                " << endl;
            cout << "------------------------------------------------" << endl;
        } while (!getNumberInput(&option,5,1));

        switch (option) {
            case 1:
                menuStack.push(&Menu::dataSetMenu);
                toyMenu();
                break;
            case 2:
                menuStack.push(&Menu::dataSetMenu);
                mediumMenu();
                break;
            case 3:
                menuStack.push(&Menu::dataSetMenu);
                realWorldMenu();
                break;
            case 5:
                goBack();
                break;
            default:
                throw CustomError("Menu not found", MENU_ERROR);
        }
    }
    catch (const CustomError& e){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

void Menu::toyMenu(){
    try {
        int option = 0;
        do {
            cout << "------------------------------------------------" << endl;
            cout << "            Menu -> Choose toy graph            " << endl;
            cout << "                                                " << endl;
            cout << "             1. Choose shipping.csv             " << endl;
            cout << "             2. Choose stadiums.csv             " << endl;
            cout << "             3. Choose tourism.csv              " << endl;
            cout << "             4. Go back                         " << endl;
            cout << "                                                " << endl;
            cout << "------------------------------------------------" << endl;
        } while (!getNumberInput(&option,4,1));


        switch (option) {
            case 1:
                manager->callParserImportFiles("../data/Toy-Graphs/Toy-Graphs/shipping.csv", 14, "", mode);
                menuStack.push(&Menu::toyMenu);
                algorithmMenu();
                break;
            case 2:
                manager->callParserImportFiles("../data/Toy-Graphs/Toy-Graphs/stadiums.csv", 10, "", mode);
                menuStack.push(&Menu::toyMenu);
                algorithmMenu();
                break;
            case 3:
                manager->callParserImportFiles("../data/Toy-Graphs/Toy-Graphs/tourism.csv", 5, "", mode);
                menuStack.push(&Menu::toyMenu);
                algorithmMenu();
                break;
            case 4:
                goBack();
                break;
            default:
                throw CustomError("Menu not found", MENU_ERROR);
        }
    }
    catch(const CustomError& e){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}


void Menu::mediumMenu(){
    try {
        int option = 0;

        do {
            cout << "------------------------------------------------" << endl;
            cout << "            Menu -> Choose medium graph         " << endl;
            cout << "                                                " << endl;
            cout << "             1. Choose 25 edges                 " << endl;
            cout << "             2. Choose 50 edges                 " << endl;
            cout << "             3. Choose 75 edges                 " << endl;
            cout << "             4. Choose 100 edges                " << endl;
            cout << "             5. Choose 200 edges                " << endl;
            cout << "             6. Choose 300 edges                " << endl;
            cout << "             7. Choose 400 edges                " << endl;
            cout << "             8. Choose 500 edges                " << endl;
            cout << "             9. Choose 600 edges                " << endl;
            cout << "             10. Choose 700 edges               " << endl;
            cout << "             11. Choose 800 edges               " << endl;
            cout << "             12. Choose 900 edges               " << endl;
            cout << "             13. Go back                        " << endl;
            cout << "                                                " << endl;
            cout << "------------------------------------------------" << endl;
        } while (!getNumberInput(&option,13,1));

        Parser *p = manager->getParser();
        if (p == nullptr){
            throw CustomError("Null Ptr: parser is a null ptr", ERROR);
        }
        switch (option) {
            case 1:
                p->importFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 25,
                               "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_25.csv", mode);
                menuStack.push(&Menu::mediumMenu);
                algorithmMenu();
                break;
            case 2:
                p->importFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 50,
                               "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_50.csv", mode);
                menuStack.push(&Menu::mediumMenu);
                algorithmMenu();
                break;
            case 3:
                p->importFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 75,
                               "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_75.csv", mode);
                menuStack.push(&Menu::mediumMenu);
                algorithmMenu();
                break;
            case 4:
                p->importFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 100,
                               "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_100.csv",
                               mode);
                menuStack.push(&Menu::mediumMenu);
                algorithmMenu();
                break;
            case 5:
                p->importFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 200,
                               "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_200.csv",
                               mode);
                menuStack.push(&Menu::mediumMenu);
                algorithmMenu();
                break;
            case 6:
                p->importFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 300,
                               "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_300.csv",
                               mode);
                menuStack.push(&Menu::mediumMenu);
                algorithmMenu();
                break;
            case 7:
                p->importFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 400,
                               "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_400.csv",
                               mode);
                menuStack.push(&Menu::mediumMenu);
                algorithmMenu();
                break;
            case 8:
                p->importFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 500,
                               "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_500.csv",
                               mode);
                menuStack.push(&Menu::mediumMenu);
                algorithmMenu();
                break;
            case 9:
                p->importFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 600,
                               "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_600.csv",
                               mode);
                menuStack.push(&Menu::mediumMenu);
                algorithmMenu();
                break;
            case 10:
                p->importFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 700,
                               "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_700.csv",
                               mode);
                menuStack.push(&Menu::mediumMenu);
                algorithmMenu();
                break;
            case 11:
                p->importFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 800,
                               "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_800.csv",
                               mode);
                menuStack.push(&Menu::mediumMenu);
                algorithmMenu();
                break;
            case 12:
                p->importFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 900,
                               "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_900.csv",
                               mode);
                menuStack.push(&Menu::mediumMenu);
                algorithmMenu();
                break;
            case 13:
                goBack();
                break;
            default:
                throw CustomError("Menu not found", MENU_ERROR);

        }
    }
    catch(const CustomError& e){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}


void Menu::realWorldMenu(){
    try {
        int option = 0;

        do {
            cout << "------------------------------------------------" << endl;
            cout << "            Menu -> Choose real world graph     " << endl;
            cout << "                                                " << endl;
            cout << "             1. Choose graph 1                  " << endl;
            cout << "             2. Choose graph 2                  " << endl;
            cout << "             3. Choose graph 3                  " << endl;
            cout << "             4. Go back                         " << endl;
            cout << "                                                " << endl;
            cout << "------------------------------------------------" << endl;
        } while (!getNumberInput(&option,4,1));

        Parser *p = manager->getParser();
        if (p == nullptr){
            throw CustomError("Null Ptr: parser is a null ptr", ERROR);
        }
        switch (option) {
            case 1:
                p->importFiles("../data/Real-world Graphs/Real-world Graphs/graph1/nodes.csv", 1000,
                               "../data/Real-world Graphs/Real-world Graphs/graph1/edges.csv", mode);
                menuStack.push(&Menu::realWorldMenu);
                algorithmMenu();
                break;
            case 2:
                p->importFiles("../data/Real-world Graphs/Real-world Graphs/graph2/nodes.csv", 5000,
                               "../data/Real-world Graphs/Real-world Graphs/graph2/edges.csv", mode);
                menuStack.push(&Menu::realWorldMenu);
                algorithmMenu();
                break;
            case 3:
                p->importFiles("../data/Real-world Graphs/Real-world Graphs/graph3/nodes.csv", 10000,
                               "../data/Real-world Graphs/Real-world Graphs/graph3/edges.csv", mode);
                menuStack.push(&Menu::realWorldMenu);
                algorithmMenu();
                break;
            case 4:
                goBack();
                break;
            default:
                throw CustomError("Menu not found", MENU_ERROR);

        }
    }
    catch(const CustomError& e){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}



void Menu::algorithmMenu() {
    try {

        int option = 0;
        do {
            cout << "----------------------------------------------" << endl;
            cout << "              Menu -> Algorithm               " << endl;
            cout << "                                              " << endl;
            cout << "    Algorithms (Recommended for Small Graphs) " << endl;
            cout << "                                              " << endl;
            cout << "               1. Backtracking                " << endl;
            cout << "                                              " << endl;
            cout << "    Algorithms (Recommended for Large Graphs) " << endl;
            cout << "                                              " << endl;
            cout << "         2. Triangular Approximation - Kruskal" << endl;
            cout << "         3. Triangular Approximation - Prim   " << endl;
            cout << "         4. Other Heuristic (Cristofides)     " << endl;
            cout << "         5. TSP in real World                 " << endl;
            cout << "                                              " << endl;
            cout << "          Extra Algorithms and Metrics       " << endl;
            cout << "                                              " << endl;
            cout << "                   6. Extra                   " << endl;
            cout << "                                              " << endl;
            cout << "               Go back option                 " << endl;
            cout << "                 7. Go back                   " << endl;
            cout << "----------------------------------------------" << endl;
        } while (!getNumberInput(&option,7,1));
        Result r;
        int vertex_chosen;

        switch (option) {
            case 1:
                chooseVertex(vertex_chosen);
                if (vertex_chosen == -1) {
                    algorithmMenu();
                } else if (vertex_chosen == 0) {
                    r = manager->getCoder()->backtracking();
                    displayResult(r);
                    algorithmMenu();
                } else {
                    r = manager->getCoder()->backtracking(vertex_chosen);
                    displayResult(r);
                    algorithmMenu();
                }
                break;

            case 2:
                chooseVertex(vertex_chosen);
                if (vertex_chosen == -1) {
                    algorithmMenu();
                } else if (vertex_chosen == 0) {
                    r = manager->getCoder()->triangularAproximation();
                    displayResult(r);
                    algorithmMenu();
                } else {
                    r = manager->getCoder()->triangularAproximation(vertex_chosen);
                    displayResult(r);
                    algorithmMenu();
                }
                break;
            case 3:
                chooseVertex(vertex_chosen);
                if (vertex_chosen == -1) {
                    algorithmMenu();
                } else if (vertex_chosen == 0) {
                    r = manager->getCoder()->triangularAproximation();
                    displayResult(r);
                    algorithmMenu();
                } else {
                    r = manager->getCoder()->triangularAproximation(vertex_chosen);
                    displayResult(r);
                    algorithmMenu();
                }
                break;
            case 4:
                chooseVertex(vertex_chosen);
                if (vertex_chosen == -1) {
                    algorithmMenu();
                } else if (vertex_chosen == 0) {
                    r = manager->getCoder()->cristofides();
                    displayResult(r);
                    algorithmMenu();
                } else {
                    r = manager->getCoder()->cristofides(vertex_chosen);
                    displayResult(r);
                    algorithmMenu();
                }
                break;
            case 5:
                chooseVertex(vertex_chosen);
                if (vertex_chosen == -1) {
                    algorithmMenu();
                } else if (vertex_chosen == 0) {
                    r = manager->getCoder()->realWorld();
                    displayResult(r);
                    algorithmMenu();
                } else {
                    r = manager->getCoder()->realWorld(vertex_chosen);
                    displayResult(r);
                    algorithmMenu();
                }
                break;
            case 6:
                menuStack.push(&Menu::algorithmMenu);
                extraMenu();
                break;
            case 7:
                goBack();
                break;
            default:
                throw CustomError("Menu not found", MENU_ERROR);
        }
    }
    catch(const CustomError& e){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}


void Menu::extraMenu() {
    try {
        int option = 0;
        do {

            cout << "----------------------------------------------" << endl;
            cout << "              Menu -> Extra algorithm         " << endl;
            cout << "                                              " << endl;
            cout << "              1. Lin Khernigan heuristic      " << endl;
            cout << "              2. Branch and bound             " << endl;
            cout << "              3. Held-Karp algorithm          " << endl;
            cout << "                                              " << endl;
            cout << "----------------------------------------------" << endl;
        } while (!getNumberInput(&option,4,1));
        Result r;
        int vertex_chosen;

        switch(option){
            case 1:
                chooseVertex(vertex_chosen);
                if (vertex_chosen == -1) {
                algorithmMenu();
            } else if (vertex_chosen == 0) {
                r = manager->getCoder()->linKhernigan();
                displayResult(r);
                algorithmMenu();
            } else {
                r = manager->getCoder()->linKhernigan(vertex_chosen);
                displayResult(r);
                algorithmMenu();
            }
            break;
            case 2:
                chooseVertex(vertex_chosen);
                if (vertex_chosen == -1) {
                    algorithmMenu();
                } else if (vertex_chosen == 0) {
                    r = manager->getCoder()->branchBound();
                    displayResult(r);
                    algorithmMenu();
                } else {
                    r = manager->getCoder()->branchBound(vertex_chosen);
                    displayResult(r);
                    algorithmMenu();
                }
                break;
            case 3:
                chooseVertex(vertex_chosen);
                if (vertex_chosen == -1) {
                    algorithmMenu();
                } else if (vertex_chosen == 0) {
                    r = manager->getCoder()->held_karp();
                    displayResult(r);
                    algorithmMenu();
                } else {
                    r = manager->getCoder()->held_karp(vertex_chosen);
                    displayResult(r);
                    algorithmMenu();
                }
                break;
            case 4:
                goBack();
                break;
            default:
                throw CustomError("Menu not found", MENU_ERROR);
        }
    }
    catch (const CustomError& e){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}


void Menu::exitMenu() {
    while (!menuStack.empty()) {
        menuStack.pop();
    }
    delete this;
}

void Menu::goBack() {
    try {
        if (!menuStack.empty()) {
            void (Menu::*previousMenu)() = menuStack.top();
            if (previousMenu == nullptr){
                throw CustomError("Menu not found", MENU_ERROR);
            }
            menuStack.pop();
            (this->*previousMenu)();
        } else {
            throw CustomError("Menu not found", MENU_ERROR);
        }
    }
    catch(const CustomError& e ){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}
