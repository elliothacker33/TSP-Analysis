#include <iostream>
#include "src/controller/Manager.h"

int main() {
    int size = 4;
    auto* m = new Manager(size);
    m->getParser()->importFiles("../data/Toy-Graphs/Toy-Graphs/tourism.csv",size,"");
    cout << m->getGraph()->getVertexSet().size() << endl;
    for (Vertex* v : m->getGraph()->getVertexSet()){
        cout << v->getAdj().size() << endl;
    }
    delete m;
    return 0;
}
