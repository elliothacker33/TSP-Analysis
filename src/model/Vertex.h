#ifndef TSP_ANALYSIS_VERTEX_H
#define TSP_ANALYSIS_VERTEX_H

/**
* @file Vertex.h
* @brief This file contains the Vertex header.
 */

#include <string>
#include <vector>
#include "Coordinates.h"
using namespace std;

/**
 * Initialization of other classes that operate together with vertex
 */
class Graph;
class Edge;

/**
 *
 * @class Vertex
 * @brief Represents an abstract class that represents a Vertex
 */

class Vertex {
public:
    /**
     * @constructor Vertex constructor
     */
    Vertex(int id, string label, Coordinate* coordinates);

    /**
     * @destructor Vertex destructor
     */
    ~Vertex();

    /**
     * @brief Retrieves the number of adjacent edges.
     *
     * Time Complexity: O(1)
     *
     * @return Number of adjacent edges.
     */
    int getOutDegree() const;

    /**
     * @brief Sets the number of adjacent edges.
     *
     * Time Complexity: O(1)
     *
     * @param outDegree Number of adjacent edges.
     */
    void setOutDegree(int outDegree);

    /**
    * @brief Retrieves the number of incoming edges.
    *
    * Time Complexity: O(1)
    *
    * @return Number of incoming edges.
    */
    int getInDegree() const;

    /**
     * @brief Sets the number of incoming edges.
     *
     * Time Complexity: O(1)
     *
     * @param outDegree Number of incoming edges.
     */
    void setInDegree(int inDegree);

    /**
    * @brief Checks if the vertex has been visited.
    *
    * Time Complexity: O(1)
    *
    * @return True if the vertex has been visited, false otherwise.
    */
    bool isVisited() const;

    /**
     * @brief Sets the visited state of the vertex.
     *
     * Time Complexity: O(1)
     *
     * @param isVisited The visited state to set.
     */
    void setVisited(bool isVisited);


    /**
    * @brief Adds an edge to the vertex.
    *
    * Time Compleity: O(E)
    *
    * @param t Pointer to the target vertex.
    * @param capacity Capacity of the edge.
    * @param type Type of the edge.
    * @return Pointer to the added edge.
    */
    Edge* addEdge(Vertex* t, double capacity);

    /**
     * @brief Removes an edge from the vertex.
     *
     * Time Compleity: O(E)
     *
     * @param e Pointer to the edge to be removed.
     */
    void removeEdge(const Edge* e);

    /**
     * @brief Sets the path edge of the vertex.
     *
     * Time Complexity: O(1)
     *
     * @param e Pointer to the path edge.
     */
    void setPath(Edge* e);

    /**
     * @brief Gets the path edge of the vertex.
     *
     * Time Complexity: O(1)
     *
     * @return Pointer to the path edge of the vertex.
     */
    Edge* getPath() const;


    /**
    * @brief Removes an incoming edge from the vertex.
    *
    * Time Complexity: O(E)
    *
    * @param e Pointer to the incoming edge to be removed.
    */
    void removeEdgeIncoming(const Edge* e);

    /**
     * @brief Adds an incoming edge to the vertex.
     *
     * Time Complexity: O(E)
     *
     * @param e Pointer to the incoming edge to be added.
     * @return True if the edge was successfully added, false otherwise.
     */
    bool addIncoming(Edge* e);

    /**
     * @brief Gets the vector of incoming edges.
     *
     * Time Complexity: O(1)
     *
     * @return Vector of incoming edges.
     */
    vector<Edge*> getIncoming();

    /**
     * @brief Gets the vector of adjacent edges.
     *
     * Time Complexity: O(1)
     *
     * @return Vector of adjacent edges.
     */
    vector<Edge*> getAdj();

private:
    /**
    * @brief Indicates the identifier of this vertex on the graph
    */
    int id;

    /**
     * @brief Label will be used for better display.
     * @if labels are not defined in the dataset, then label = id.
     * @else label = data set label
     */
    string label;

    /**
     * @brief Pointer to coordinates of the vertex in the graph
     * @if The graph dont allow for coordinates, it will point to nullptr.
    */
     Coordinate* coordinates = nullptr;


    /**
     * @brief Indicates whether the vertex has been visited.
     *
     * This boolean field is used to track whether the vertex has been visited during graph traversal algorithms.
     * By default, it is initialized to false.
     */
    bool visited = false;


    /**
     * @brief Stores the out-degree of the vertex.
     *
     * This integer field represents the number of outgoing edges from the vertex.
     * By default, it is initialized to 0.
     */
    int outDegree = 0;

    /**
     * @brief Stores the in-degree of the vertex.
     *
     * This integer field represents the number of incoming edges to the vertex.
     * By default, it is initialized to 0.
     */
    int inDegree = 0;

    /**
     * @brief Stores the adjacent edges of the vertex.
     *
     * This vector stores pointers to the edges that are adjacent to the vertex.
     * It represents the edges going out from the vertex.
     */
    vector<Edge*> adj;

    /**
     * @brief Stores the incoming edges of the vertex.
     *
     * This vector stores pointers to the edges that are incoming to the vertex.
     * It represents the edges coming into the vertex.
     */
    vector<Edge*> incoming;

    /**
     * @brief Pointer to the path edge of the vertex.
     *
     * This pointer stores the path edge associated with the vertex during graph traversal algorithms.
     * It points to the edge that leads to this vertex from its predecessor in the traversal.
     * By default, it is initialized to nullptr.
     */
    Edge* path = nullptr;

};




#endif //TSP_ANALYSIS_VERTEX_H
