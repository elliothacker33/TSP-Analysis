/**
 *
* @file Menu.cpp
* @brief This file contains the Menu implementation.
*/
// Project headers
#include "Menu.h"
// Standard Library Headers
#include <sstream>
#include <filesystem>


Menu::~Menu() {
    delete manager;
}

Menu::Menu(Manager* manager) {
    if (manager == nullptr) {
        throw CustomError("NullPtr: Manager is a null ptr", ERROR);
    }
    this->manager = manager;
    this->mode = false; // Default mode : Real World
}

/* Auxiliary functions */
string Menu::removeLeadingTrailingSpaces(const string& input) {
    const auto start = input.find_first_not_of(" \n\r\t");
    const auto end = input.find_last_not_of(" \n\r\t");

    return (start != string::npos && end != string::npos) ? input.substr(start, end - start + 1) : "";
}

Folder Menu::getFolderContents(const string& path){
    Folder files;
    for (const auto& entry: filesystem::directory_iterator(path)){
        if (entry.is_regular_file()){
            files.push_back(entry.path().generic_string());
        }
    }
    return files;
}

Folder Menu::getFoldersInFolder(const string& path){
    Folder folders;
    for (const auto& entry: filesystem::directory_iterator(path)){
        if (entry.is_directory()){
            folders.push_back(entry.path().filename());
        }
    }
    return folders;
}

/* Get Input functions */

bool Menu::getNumberInput(int* option, int maxInput,int minInput) {
    cout << "Enter your choice (" << 1 << "-" << maxInput << "): ";
    string s_input;
    getline(cin, s_input);
    string trimmedInput = removeLeadingTrailingSpaces(s_input);
    stringstream ss(trimmedInput);
    int input;
    ss >> input;

    if (isNumber(trimmedInput) && input >= minInput && input <= maxInput) {
        *option = input;
        return true;
    }

    cout << "Invalid input. Please enter a number between " << 1 << " and " << maxInput << endl;
    return false;
}

bool Menu::askNumberOfVertices(int * n) {
    cout << "Enter the number of vertices of your dataset: ";
    string s_input;
    getline(cin, s_input);
    string trimmedInput = removeLeadingTrailingSpaces(s_input);
    stringstream ss(trimmedInput);
    int input;
    ss >> input;

    if (isNumber(trimmedInput)) {
        *n = input;
        return true;
    }

    return false;
}



bool Menu::isNumber(string number){
    auto it = number.begin();
    while(it != number.end() && isdigit(*it)){
        it++;
    }
    return !number.empty() && it == number.end();
}
/* Get vertex examples */

void Menu::chooseVertex(int &vertex_id) {
    string input;
    HashTable *table = manager->getVerticesTable();

    while (true) {
        getVertexExamples();
        cout << "Enter a valid vertex id, press 'DEFAULT' for default, or press 'STOP' to stop inserting: " << endl;
        getline(cin, input);
        input = removeLeadingTrailingSpaces(input);

        if (input == "STOP" || input == "stop") {
            vertex_id = -1;
            return;
        } else if (input == "DEFAULT" || input == "default") {
            vertex_id = 0;
            return;
        } else {
                if (isNumber(input)){
                    vertex_id = stoi(input);
                    if (table->search(vertex_id) != nullptr) {
                        return;
                    }
                    else{
                        cout << "The inserted vertex id is not present in the table." << endl;
                    }
                }
                else {
                    cout << "Input is a not an integer" << endl;
                }

        }
    }
}

void Menu::getVertexExamples(){
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


/** Results functions **/

void Menu::displayResult(const Result& r){
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

/** Menus **/

void Menu::mainMenu() {
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


void Menu::dataSetMenu() {
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
        case 4:
            menuStack.push(&Menu::dataSetMenu);
            yourDataSetMenu();
        case 5:
            goBack();
            break;
        default:
            throw CustomError("Menu not found", MENU_ERROR);
    }
}

void Menu::yourDataSetMenu(){
    int option = 0;
    Folder f;
    do {
        cout << "------------------------------------------------" << endl;
        cout << "         Menu -> Choose your own data set       " << endl;
        f = getFoldersInFolder("../data/My_Graphs");
        int count = 1;
        for (const auto& file: f){
            cout << "            " << count << ". " << file << "        " << endl;
            count++;
        }
        cout << "            " << count << ". Go back" << "         " << endl;
        cout << "------------------------------------------------" << endl;

    }
    while(!getNumberInput(&option,static_cast<int>(f.size() + 1),1));

    if (option == f.size() + 1){
        goBack();
    }
    else{
        menuStack.push(&Menu::yourDataSetMenu);
        Folder files  = getFolderContents("../data/My_Graphs/" + f[option - 1]);
        if (files.size() == 2){
            int n;
            cout << "This number needs to be exactly the size to work!!!" << endl;
            while(!askNumberOfVertices(&n)){
                cout << "Invalid input. Enter a integer" << endl;
            }
            cout << "../data/My_Graphs/" + f[option - 1] + "/nodes.csv" << endl;

            manager->callParserImportFiles("../data/My_Graphs/" + f[option - 1] + "/nodes.csv", n, "../data/My_Graphs/" + f[option - 1] + "/edges.csv" ,mode);

        }
        else if (files.size() == 1){
            int n;
            cout << "This number needs to be exactly the size to work!!!" << endl;
            while(!askNumberOfVertices(&n)){
                cout << "Invalid input. Enter a integer" << endl;
            }
            manager->callParserImportFiles("../data/My_Graphs/" + f[option - 1] + "/nodes.csv", n, "" ,mode);
        }
        else{
            throw CustomError("Wrong number of files", MENU_ERROR);
        }
        algorithmMenu();
    }
}


void Menu::toyMenu(){
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



void Menu::mediumMenu(){
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

    switch (option) {
        case 1:
            manager->callParserImportFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 25,
                           "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_25.csv", mode);
            menuStack.push(&Menu::mediumMenu);
            algorithmMenu();
            break;
        case 2:
            manager->callParserImportFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 50,
                           "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_50.csv", mode);
            menuStack.push(&Menu::mediumMenu);
            algorithmMenu();
            break;
        case 3:
            manager->callParserImportFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 75,
                           "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_75.csv", mode);
            menuStack.push(&Menu::mediumMenu);
            algorithmMenu();
            break;
        case 4:
            manager->callParserImportFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 100,
                           "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_100.csv",
                           mode);
            menuStack.push(&Menu::mediumMenu);
            algorithmMenu();
            break;
        case 5:
            manager->callParserImportFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 200,
                           "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_200.csv",
                           mode);
            menuStack.push(&Menu::mediumMenu);
            algorithmMenu();
            break;
        case 6:
            manager->callParserImportFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 300,
                           "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_300.csv",
                           mode);
            menuStack.push(&Menu::mediumMenu);
            algorithmMenu();
            break;
        case 7:
            manager->callParserImportFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 400,
                           "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_400.csv",
                           mode);
            menuStack.push(&Menu::mediumMenu);
            algorithmMenu();
            break;
        case 8:
            manager->callParserImportFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 500,
                           "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_500.csv",
                           mode);
            menuStack.push(&Menu::mediumMenu);
            algorithmMenu();
            break;
        case 9:
            manager->callParserImportFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 600,
                           "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_600.csv",
                           mode);
            menuStack.push(&Menu::mediumMenu);
            algorithmMenu();
            break;
        case 10:
            manager->callParserImportFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 700,
                           "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_700.csv",
                           mode);
            menuStack.push(&Menu::mediumMenu);
            algorithmMenu();
            break;
        case 11:
            manager->callParserImportFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 800,
                           "../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_800.csv",
                           mode);
            menuStack.push(&Menu::mediumMenu);
            algorithmMenu();
            break;
        case 12:
            manager->callParserImportFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv", 900,
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


void Menu::realWorldMenu(){
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

    switch (option) {
        case 1:
            manager->callParserImportFiles("../data/Real-world Graphs/Real-world Graphs/graph1/nodes.csv", 1000,
                           "../data/Real-world Graphs/Real-world Graphs/graph1/edges.csv", mode);
            menuStack.push(&Menu::realWorldMenu);
            algorithmMenu();
            break;
        case 2:
            manager->callParserImportFiles("../data/Real-world Graphs/Real-world Graphs/graph2/nodes.csv", 5000,
                           "../data/Real-world Graphs/Real-world Graphs/graph2/edges.csv", mode);
            menuStack.push(&Menu::realWorldMenu);
            algorithmMenu();
            break;
        case 3:
            manager->callParserImportFiles("../data/Real-world Graphs/Real-world Graphs/graph3/nodes.csv", 10000,
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



void Menu::algorithmMenu() {
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
        cout << "         2. Triangular Approximation - Prim   " << endl;
        cout << "         3. Other Heuristic (Cristofides)     " << endl;
        cout << "         4. TSP in real World                 " << endl;
        cout << "                                              " << endl;
        cout << "          Extra Algorithms and Metrics       " << endl;
        cout << "                                              " << endl;
        cout << "                   5. Extra                   " << endl;
        cout << "                                              " << endl;
        cout << "               Go back option                 " << endl;
        cout << "                 6. Go back                   " << endl;
        cout << "----------------------------------------------" << endl;
    } while (!getNumberInput(&option,6,1));
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
                r = manager->getCoder()->triangularApproximation();
                displayResult(r);
                algorithmMenu();
            } else {
                r = manager->getCoder()->triangularApproximation(vertex_chosen);
                displayResult(r);
                algorithmMenu();
            }
            break;
        case 3:
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
        case 4:
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
        case 5:
            menuStack.push(&Menu::algorithmMenu);
            extraMenu();
            break;
        case 6:
            goBack();
            break;
        default:
            throw CustomError("Menu not found", MENU_ERROR);
    }
}


void Menu::extraMenu() {
    int option = 0;
    do {

        cout << "----------------------------------------------" << endl;
        cout << "              Menu -> Extra algorithm         " << endl;
        cout << "                                              " << endl;
        cout << "              1. Lin Khernigan heuristic      " << endl;
        cout << "              2. Branch and bound             " << endl;
        cout << "              3. Held-Karp algorithm          " << endl;
        cout << "              4. Go back                      " << endl;
        cout << "                                              " << endl;
        cout << "----------------------------------------------" << endl;
    } while (!getNumberInput(&option,4,1));
    Result r;
    int vertex_chosen;

    switch(option){
        case 1:
            chooseVertex(vertex_chosen);
            if (vertex_chosen == -1) {
            extraMenu();
        } else if (vertex_chosen == 0) {
            r = manager->getCoder()->linKhernigan();
            displayResult(r);
            extraMenu();
        } else {
            r = manager->getCoder()->linKhernigan(vertex_chosen);
            displayResult(r);
            extraMenu();
        }
        break;
        case 2:
            chooseVertex(vertex_chosen);
            if (vertex_chosen == -1) {
                extraMenu();
            } else if (vertex_chosen == 0) {
                r = manager->getCoder()->branchBound();
                displayResult(r);
                extraMenu();
            } else {
                r = manager->getCoder()->branchBound(vertex_chosen);
                displayResult(r);
                extraMenu();
            }
            break;
        case 3:
            chooseVertex(vertex_chosen);
            if (vertex_chosen == -1) {
                extraMenu();
            } else if (vertex_chosen == 0) {
                r = manager->getCoder()->held_karp();
                displayResult(r);
                extraMenu();
            } else {
                r = manager->getCoder()->held_karp(vertex_chosen);
                displayResult(r);
                extraMenu();
            }
            break;
        case 4:
            goBack();
            break;
        default:
            throw CustomError("Menu not found", MENU_ERROR);
    }
}


void Menu::exitMenu() {
    while (!menuStack.empty()) {
        menuStack.pop();
    }
    delete this;
}

void Menu::goBack() {
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
