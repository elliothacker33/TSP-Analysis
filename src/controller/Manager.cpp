#include "Manager.h"

Manager::Manager(int number_of_vertices) {
    this->graph = new Graph();
    this->vertices_table = new HashTable(number_of_vertices);
    this->parser = new Parser(graph,vertices_table);
    this->coder = new Coder(graph,vertices_table);
}

Manager::~Manager() {
    // Delete graph/parser/hash_table
    delete this->vertices_table;
    delete this->graph;
    delete this->parser;
    delete this->coder;
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

Coder* Manager::getCoder() const {
    return this->coder;
}




void Manager::resetManager(int number_of_vertices) {
    // Delete graph/parser/hash_table
    delete this->vertices_table;
    delete this->graph;
    delete this->parser;
    delete this->coder;

    // Create new ones
    this->graph = new Graph();
    this->vertices_table = new HashTable(number_of_vertices);
    this->parser = new Parser(graph,vertices_table);
    this->coder = new Coder(graph,vertices_table);
}
void Manager::resetGraph() {

}

