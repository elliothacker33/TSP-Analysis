/**
* @file Graph.cpp
* @brief This file contains the implementation of Graph.
*/

/**< Project headers >**/
#include "Graph.h"

Graph::~Graph() {
    while (!vertexSet.empty()) {
        auto it = vertexSet.begin();
        removeVertex(*it);
    }
}

bool Graph::addVertex(Vertex *v) {
    for (const auto ve : vertexSet) {
        if (ve->getId() == v->getId()) {
            return false;
        }
    }
    vertexSet.push_back(v);
    n++;
    return true;
}


void Graph::removeVertex(Vertex* v) {
    auto it = vertexSet.begin();
    while (it != vertexSet.end()) {
        if ((*it)->getId() == v->getId()) {
            vertexSet.erase(it);
            n--;
            delete v;
            return;
        }
        ++it;
    }
}

void Graph::resetVisited() const{
    for(auto v: getVertexSet()){
        v->setVisited(false);
    }
}


void Graph::removeEdge(const Edge *edge) {
    edge->getOrigin()->removeEdge(edge);
    delete edge;
}


vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}


int Graph::getNumberOfVertexes() const {
    return n;
}


Edge* Graph::addEdge(Vertex *orig, Vertex *dest, double distance) {
    Edge* result = orig->addEdge(dest,distance);
    return result;
}


