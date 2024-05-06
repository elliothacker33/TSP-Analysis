#include <iostream>
#include "src/controller/Manager.h"


int main() {
    int size = 5;
    auto* m = new Manager(size);
    m->getParser()->importFiles("../data/Toy-Graphs/Toy-Graphs/tourism.csv",size,"",true);
    vector<Vertex*> tour;
    m->getCoder()->buildInitialRandomTour(0,tour);
    for (auto v: tour){
        cout << v->getId() << endl;
    }
    cout << endl;
    delete m;
    return 0;
}


