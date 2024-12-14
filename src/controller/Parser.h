#ifndef TSP_ANALYSIS_PARSER_H
#define TSP_ANALYSIS_PARSER_H

/**
 * @file Parser.h -> Header file for parser
 */

/**< Project headers >**/
#include "../model/Graph.h"
#include "HashTable.h"
/**< STD headers >**/
#include <string>


/**
 * @class Parser -> Class parser that is used to import graphs to test TSP
 */
class Parser {
public:
    /**
     * @brief  Set new table for new imports
     * @param table -> vertices table
     */
    void setNewTable(HashTable* table);
    /**
     * @brief Set new graph
     * @param graph -> pointer to graph
     */
    void setNewGraph(Graph* graph);

    /**
     * @brief This method is a interface function that builds a Graph from a file
     * @param vertices_path -> Vertices file path
     * @param edges_path -> Edges file path
     * @param number_of_vertices -> number of vertices to process
     * @param symmetric_or_real -> Is the graph symmetric edges, or just save what needs to be processed. (True - symmetric, False - real)
     */
    void importFiles(const string& vertices_path, int number_of_vertices, const string& edges_path, bool symmetric_or_real);

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
     * @param symmetric_or_real -> Is the graph symmetric edges, or just save what needs to be processed (True - symmetric, False - real).
     */
    void importEdges(const string& file_path, bool symmetric_or_real);

    /**
     * Import vertices and edges at same time.
     * @param file_path - path containing both vertices and edges
     * @param graph - pointer to graph
     * @param symmetric_or_real -> Is the graph symmetric edges, or just save what needs to be processed (True - symmetric, False - real).
     */
    void importVerticesWithEdges(const string& file_path, bool symmetric_or_real);

    Graph* graph = nullptr; /**< Pointer to graph >**/
    HashTable* vertices_table = nullptr; /**< Pointer to table >**/

};


#endif //TSP_ANALYSIS_PARSER_H