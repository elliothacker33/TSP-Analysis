/**
* @file Edge.cpp
* @brief This file contains the implementation of Edge.
 */

/**< Project headers >**/
#include "Edge.h"
#include "Vertex.h"

Edge::Edge(Vertex* origin, Vertex* destination, double distance) {
    this->origin = origin;
    this->destination = destination;
    this->distance = distance;
}

double Edge::getDistance() const {
    return this->distance;
}

void Edge::setDistance(double _distance) {
    this->distance = _distance;
}

Vertex* Edge::getOrigin() const {
    return this->origin;
}

Vertex* Edge::getDestination() const {
    return this->destination;
}

Edge* Edge::getReverseEdge() const {
    return this->reverse;
}

void Edge::setReverseEdge(Edge* _reverse) {
    if (_reverse != nullptr){
        this->reverse = _reverse;
    }
}
