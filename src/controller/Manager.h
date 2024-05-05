
#ifndef TSP_ANALYSIS_MANAGER_H
#define TSP_ANALYSIS_MANAGER_H

/**< Project headers >**/
#include "../model/Graph.h"
#include "Parser.h"
#include "HashTable.h"
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
    explicit Manager(int number_of_vertices);

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
     * Get vertices used by manager
     * @return vertices
     */
    [[nodiscard]] HashTable* getVerticesTable() const;

    /**
     * @brief Reset graph
     */
    void resetGraph();

    /**
     * @brief Reset manager
     * @if manager is not initialized don't reset it.
     */
    void resetManager(int n);

    /**
     * @destructor Destructor for class manager
     */
    ~Manager();

protected:
    Parser* parser; /**< Parser >**/
    Graph* graph;  /**< Graph >**/
    HashTable* vertices_table; /**< Vertices table >**/
};




/*
 *
class CodeManager{
public:

};
 */


// It's also possible the need for AnalysisDataManager

#endif //TSP_ANALYSIS_MANAGER_H
