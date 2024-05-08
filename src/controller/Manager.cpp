#include "Manager.h"

Manager::Manager() {
    this->graph = new Graph();
    this->parser = new Parser();
    this->vertices_table = new HashTable(10);
    this->coder = new Coder();
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
    this->parser = new Parser();
    this->coder = new Coder();
}


void Manager::callParserImportFiles(const string &vertices_path, int number_of_vertices, const string &edges_path,bool symmetric_or_real) {
    delete this->vertices_table;
    delete this->graph;
    this->graph = new Graph();
    this->vertices_table = new HashTable(number_of_vertices);
    this->parser->setNewTable(vertices_table);
    this->parser->setNewGraph(graph);
    this->coder->setNewTable(vertices_table);
    this->coder->setNewGraph(graph);
    parser->importFiles(vertices_path,number_of_vertices,edges_path,symmetric_or_real);
}

