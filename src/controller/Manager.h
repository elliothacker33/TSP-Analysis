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
#include "Visualizer.h"
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
     * @brief Get vertices used by manager
     * @note Our hashtable uses open-addressing with linear probing
     * @return vertices
     */
    [[nodiscard]] HashTable* getVerticesTable() const;

    /**
     * @brief Get coder, interface for algorithms
     */
     [[nodiscard]] Coder* getCoder() const;

     /**
      * @brief Visualizer is used to display better the results obtained in the coder
      * Algorithm class uses the results stored in the Coder
      */
     [[nodiscard]] Visualizer* getVisualizer() const;


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

private:
    Parser* parser; /**< Parser >**/
    Graph* graph;  /**< Graph >**/
    HashTable* vertices_table; /**< Vertices table >**/
    Coder* coder; /**< Coder >**/
};

#endif //TSP_ANALYSIS_MANAGER_H
