#include "Manager.h"

Manager::Manager(int n) {
    this->graph = new Graph();
    this->vertices_table = new HashTable(n);
    this->parser = new Parser(graph,vertices_table);

}

Manager::~Manager(){
    // Delete graph/parser/hash_table
    delete this->vertices_table;
    delete this->graph;
    delete this->parser;
}

Graph* Manager::getGraph() const {
    return this->graph;
}

Parser* Manager::getParser() const {
    return this->parser;
}

HashTable* Manager::getVerticesTable() const {
    return this->vertices_table;
}


void Manager::resetManager(int n) {
    // Delete graph/parser/hash_table
    delete this->vertices_table;
    delete this->graph;
    delete this->parser;

    // Create new ones
    this->graph = new Graph();
    this->vertices_table = new HashTable(n);
    this->parser = new Parser(graph,vertices_table);
}
void Manager::resetGraph() {

}

