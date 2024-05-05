#ifndef TSP_ANALYSIS_PARSER_H
#define TSP_ANALYSIS_PARSER_H

/**< Project headers >**/
#include "../model/Graph.h"
#include "HashTable.h"
/**< STD headers >**/
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

class Parser {
public:
    Parser(Graph* graph, HashTable* table);
    /**
     * @brief This method is a interface function that builds a Graph from a file
     * @param vertices_path -> Vertices file path
     * @param edges_path -> Edges file path
     */
    void importFiles(const string& vertices_path, int number_of_vertices, const string& edges_path);

private:

    /**
     * @brief Import vertices
     * @param file_path - vertices path
     * @param graph - pointer to graph
     */
    void importVertices(const string& file_path, int number_of_vertices);

    /**
     * @breif Import edges
     * @param file_path - edges path
     * @param graph - pointer to graph
     */
    void importEdges(const string& file_path);

    /**
     * Import vertices and edges at same time.
     * @param file_path - path containing both vertices and edges
     * @param graph - pointer to graph
     */
    void importVerticesWithEdges(const string& file_path);

    Graph* graph;
    HashTable* vertices_table;

};


#endif //TSP_ANALYSIS_PARSER_H
