/**
* @file Vertex.cpp
* @brief This file contains the implementation of Vertex.
 */

/**< Project headers >**/
#include "Vertex.h"
#include "Edge.h"

/**< STD headers >**/
#include <sstream>
#include <algorithm>

Vertex::~Vertex(){
    // Delete edges
    for (const Edge* edge : adj) {
        delete edge;
    }
    adj.clear();
    incoming.clear();

    // Delete coordinates
    delete coordinates;
}

Vertex::Vertex(int id, string& label, Coordinate* coordinates) {
    this->id = id;
    if (label.empty()){
        stringstream ss;
        ss << id;
        this->label = ss.str();
    }
    this->label = label;
    if (coordinates != nullptr)
        this->coordinates = coordinates;
}

vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

vector<Edge*> Vertex::getIncoming() const {
    return this->incoming;
}

int Vertex::getId() const {
    return this->id;
}

[[maybe_unused]] void Vertex::setId(int _id) {
    this->id = _id;
}

Coordinate* Vertex::getCoordinates() const {
    return this->coordinates;
}

const string& Vertex::getLabel() const {
    return this->label;
}

void Vertex::setLabel(string &_label) {
    this->label = _label;
}

int Vertex::getOutDegree() const {
    return this->outDegree;
}

int Vertex::getInDegree() const {
    return this->inDegree;
}

void Vertex::setOutDegree(const int _outDegree) {
    this->outDegree = _outDegree;
}

void Vertex::setInDegree(int _inDegree) {
    this->inDegree = _inDegree;
}

bool Vertex::isVisited() const {
    return this->visited;
}

void Vertex::setVisited(bool _visited) {
    this->visited = _visited;
}

Edge* Vertex::getPath() const {
    return this->path;
}

void Vertex::setPath(Edge* _path) {
    this->path = _path;
}

void Vertex::addIncoming(Edge* edge) {
    int id_origin = edge->getOrigin()->getId() ;
    int id_destination = edge->getDestination()->getId();

    // Check if edge already exists
    for (const auto e : this->incoming) {
        if (id_origin == e->getOrigin()->getId() && id_destination == e->getDestination()->getId()) {
            return;
        }
    }
    // Add edge to incoming
    this->incoming.push_back(edge);
    this->inDegree++;
}

Edge *Vertex::addEdge(Vertex * destination, double capacity) {
    int _id = destination->getId();

    // Check if edge already exists
    for (const auto e : this->adj) {
        if (Vertex* dest = e->getDestination(); dest->getId() == _id) {
            return nullptr;
        }
    }
    // Build edges in the adjacent of this and in the incoming of destination
    auto* edge = new Edge(this,destination,capacity);
    this->adj.push_back(edge);
    outDegree++;
    destination->addIncoming(edge);
    return edge;
}

void Vertex::removeEdge(const Edge *edge) {
    adj.erase(remove_if(adj.begin(), adj.end(), [&](const Edge* e) {
        if (e->getOrigin()->getId() == edge->getOrigin()->getId() && e->getDestination()->getId() == edge->getDestination()->getId()) {
            return true;
        }
        return false;
    }), adj.end());

    this->outDegree--;
    edge->getDestination()->removeEdgeIncoming(edge);
}

void Vertex::removeEdgeIncoming(const Edge* edge) {
    incoming.erase(remove_if(incoming.begin(), incoming.end(), [&](const Edge* e) {
        if (e->getOrigin()->getId() == edge->getOrigin()->getId() && e->getDestination()->getId() == edge->getDestination()->getId()) {
            return true;
        }
        return false;
    }), incoming.end());
    this->inDegree--;
}






