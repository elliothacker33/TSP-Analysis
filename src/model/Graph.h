#ifndef TSP_ANALYSIS_GRAPH_H
#define TSP_ANALYSIS_GRAPH_H

/**
* @file Graph.h
* @brief This file contains the Graph header.
 */

/**< Project headers >**/
#include "Edge.h"
#include "Vertex.h"

/**< STD headers >**/
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**
 * @class Graph
 * @brief Represents a graph data structure.
 *
 * This class represents a graph data structure consisting of vertices and edges.
 */
class Graph {
public:
    /**
    * @brief Destructor for the Graph class.
    * This destructor cleans up the memory allocated for the graph's vertices and edges.
    */
    ~Graph();

    /**
     * @brief Gets the vector of vertices in the graph.
     * @return Vector containing pointers to the vertices in the graph.
     */
    [[nodiscard]] vector<Vertex*> getVertexSet() const;

    /**
    * @brief Gets the number of vertices in the graph.
    * @return The number of vertices in the graph.
    */
    [[nodiscard]] int getNumberOfVertexes() const;

    /**
    * @brief Adds a vertex to the graph.
    * @param v Pointer to the vertex to be added.
    * @return True if the vertex was successfully added, false otherwise.
    */
    bool addVertex(Vertex* v);

    /**
    * @brief Reset all visited vertices to false
    */
    void resetVisited() const;

    /**
    * @brief Removes a vertex from the graph.
    * @param v Pointer to the vertex to be removed.
    */
    void removeVertex(Vertex* v);

    /**
    * @brief Adds an edge between two vertices in the graph.
    * @param orig Pointer to the origin vertex of the edge.
    * @param dest Pointer to the destination vertex of the edge.
    * @param capacity Capacity of the edge.
    * @param type Type of the edge.
    * @return Pointer to the added edge.
    */
    Edge* addEdge(Vertex* origin, Vertex* destination, double distance);

    /**
     * @brrief Remove edge from the graph
     * @param edge
     */
    void removeEdge(const Edge *edge);


private:
    vector<Vertex*> vertexSet; /**< Vector containing pointers to the vertices of the graph. */
    int n = 0; /**< The number of vertices in the graph. */

};
#endif //TSP_ANALYSIS_GRAPH_H
