#include <iostream>
#include "src/controller/Manager.h"

int main() {
    int size = 900;
    auto* m = new Manager(size);
    m->getParser()->importFiles("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/nodes.csv",size,"../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_900.csv");
    cout << m->getGraph()->getVertexSet().size() << endl;
    delete m;
    return 0;
}
