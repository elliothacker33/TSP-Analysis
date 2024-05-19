#ifndef TSP_ANALYSIS_MANAGER_H
#define TSP_ANALYSIS_MANAGER_H
/**
 * @file Manager.h
 * @brief Header for manager
 */

/**< Project headers >**/
#include "../model/Graph.h"
#include "Parser.h"
#include "HashTable.h"
#include "Coder.h"
/**< STD headers >**/
#include <unordered_map>

/**
 * @note Our way of doing multiple managers, respects the SRP- Single responsibility principle
 */

class Manager {
public:
    /**
     * @constructor Constructor for class manager
     * @param n
     */
    Manager();

    /**
     * Get the graph used by the managers
     * @return graph
     */
    [[nodiscard]] Graph* getGraph() const;

    /**
     * Get parser used by manager
     * @return parser
     */
    [[nodiscard]] Parser* getParser() const;

    /**
     * @brief Get vertices used by manager
     * @note Our hashtable uses open-addressing with linear probing
     * @return vertices
     */
    [[nodiscard]] HashTable* getVerticesTable() const;

    /**
     * @brief Get coder, interface for algorithms
     */
     [[nodiscard]] Coder* getCoder() const;

     void callParserImportFiles(const string& vertices_path, int number_of_vertices, const string& edges_path, bool symmetric_or_real);


    /**
     * @destructor Destructor for class manager
     */
    ~Manager();

private:
    Parser* parser; /**< Parser >**/
    Graph* graph;  /**< Graph >**/
    HashTable* vertices_table; /**< Vertices table >**/
    Coder* coder; /**< Coder >**/
};

#endif //TSP_ANALYSIS_MANAGER_H
