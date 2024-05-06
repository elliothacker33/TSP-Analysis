#include <iostream>
#include "src/controller/Manager.h"


int main() {
    int size = 5;
    auto* m = new Manager(size);
    m->getParser()->importFiles("../data/Toy-Graphs/Toy-Graphs/tourism.csv",size,"",true);
    Result r = m->getCoder()->backtracking(0);
    cout << r.distance << " " << r.time_spent.elapsed_real << " " << r.time_spent.elapsed_cpu<< endl;
    for(auto v : r.path){
        cout << v->getId() << " ,";
    }
    cout << endl;
    delete m;
    return 0;
}


