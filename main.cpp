#include <iostream>
#include "src/controller/Manager.h"

int main() {
    int size = 4;
    auto* m = new Manager(size);
    m->getParser()->importFiles("../data/Toy-Graphs/Toy-Graphs/tourism.csv",size,"");
    cout << m->getGraph()->getNumberOfVertexes() << endl;
    delete m;
    return 0;
}
