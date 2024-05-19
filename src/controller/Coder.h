#ifndef TSP_ANALYSIS_CODER_H
#define TSP_ANALYSIS_CODER_H

/**< Project header >**/
#include "HashTable.h"
#include "../model/Graph.h"
#include "../Exceptions/CustomError.h"

/**
 * @struct Time
 * @param elapsed_real
 * @param elapsed_cpu
 */
struct Time {
    double elapsed_real;
    double elapsed_cpu;
};

/**
 * @struct Result
 * @param path
 * @param distance
 * @param time_spent
 */
 typedef vector<Edge*> Tour;
struct Result {
    Tour tour;
    double distance;
    Time time_spent;
};

/**
 * @class Coder - class that contains the algorithms
 */
class Coder {
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
     * @brief Backtracking algorithm (more used for small graphs)
     * @Complexity - O(b^d), where b is the branching factor and d is the depth of the recursion tree
     * @return Result
     */
    Result backtracking(int start_vertex = 0);

    /**
     * @brief Branch and Bound algorithm (more efficient than backtracking)
     * @Complexity -O(V)
     * @return Result
     */
    Result branchBound(int start_vertex = 0);

    /**
     * @brief Approximates the shortest Hamiltonian cycle using triangular approximation algorithm.
     *
     * This function calculates an approximation of the shortest Hamiltonian cycle starting from the specified vertex.
     * It employs Prim's algorithm to build a minimum spanning tree (MST) and then adds a cycle edge to complete the cycle.
     * The total distance of the cycle and the time taken for the computation are returned.
     *
     * @Complexity - O(V^2)
     *
     * @param start_vertex - The vertex from which to start building the Hamiltonian cycle.
     * @return A ResultCoder object containing the Hamiltonian cycle, its total distance, and the time taken for computation.
     */
    Result triangularApproximation(int start_vertex = 0);

    /**
     * @brief
     *
     * @Complexity
     *
     * @param start_vertex -
     * @return
     */
    Result cristofides(int start_vertex = 0);

    /**
     * @brief
     *
     * @Complexity
     *
     * @param start_vertex -
     * @return
     */
    Result nearestNeighbor(int start_vertex = 0);


    /**
     * @brief
     *
     * @Complexity
     *
     * @param start_vertex -
     * @return
     */
    Result realWorld(int start_vertex = 0);



private:
    /**
     * @brief Starts a timer to measure real and CPU time.
     *
     * This function starts a timer to measure both real and CPU time.
     * Real time is measured using CLOCK_REALTIME, which represents the actual time elapsed.
     * CPU time is measured using CLOCK_PROCESS_CPUTIME_ID, which represents the CPU time consumed by the calling process.
     *
     * @Complexity - O(1)
     *
     * @param start_real Reference to a timespec structure to store the start time of real time.
     * @param start_cpu Reference to a timespec structure to store the start time of CPU time.
     */
    static void startTimer(timespec& start_real, timespec& start_cpu);

    /**
     * @brief Stops the timer and calculates the elapsed real and CPU time.
     *
     * This function stops the timer, retrieves the end time for both real and CPU time,
     * and calculates the elapsed time for both real and CPU time.
     *
     * @Complexity - O(1)
     *
     * @param start_real The start time of real time.
     * @param start_cpu The start time of CPU time.
     * @param elapsed_real Reference to a double variable to store the elapsed real time.
     * @param elapsed_cpu Reference to a double variable to store the elapsed CPU time.
     * @return A Time object containing the elapsed real and CPU time.
     */
    static Time stopTimer(timespec& start_real, timespec& start_cpu, double& elapsed_real, double& elapsed_cpu);

    /**
     * @brief Checks if the graph is complete.
     *
     * This function checks if the graph is complete, meaning each vertex is adjacent to every other vertex.
     *
     * @Complexity - O(V^2)
     *
     * @return True if the graph is complete, otherwise false.
     */
    bool isGraphComplete();

    /**
     * @brief Checks if the graph is symmetric.
     *
     * This function checks if the graph is symmetric, meaning for each edge from vertex A to vertex B,
     * there is a corresponding edge from vertex B to vertex A with the same weight.
     *
     * @Complexity -  O(V * E^2)
     *
     * @return True if the graph is symmetric, otherwise false.
     */
    bool isGraphSymmetric();

    /**
     * @brief Visits vertices in pre-order traversal starting from the given vertex.
     *
     * This function performs a pre-order traversal starting from the given vertex.
     * It visits each vertex and its adjacent vertices in pre-order, adding them to the provided vector.
     *
     * @Complexity - O(V)
     *
     * @param current The current vertex being visited.
     * @param t Reference to a vector to store the vertices visited in pre-order.
     */
    void preOrderVisit(Vertex* current, vector<Vertex*>& t);

    /**
     * @brief Calculates the total cost of a tour.
     *
     *  This function calculates the total cost of traversing a tour, which is the sum of distances
     *  of all edges in the tour.
     *
     * @complexity - O(n), where n is the number of edges in the tour.
     *
     * @param tour The tour for which to calculate the total cost.
     * @return The total cost of traversing the tour.
     */
    double calculateTourCost(const Tour& tour);



    /**
     * @brief Calculates the Haversine distance between two vertices on the Earth's surface.
     *
     * This function calculates the Haversine distance, which is the shortest distance over the earth's surface
     * given the longitude and latitude coordinates of two points.
     *
     * @Complexity - O(1)
     *
     * @param origin Pointer to the origin vertex.
     * @param destination Pointer to the destination vertex.
     * @return The Haversine distance between the origin and destination vertices in meters.
     */
    static double haversineDistance(Vertex* origin, Vertex* destination);


    /**
     * @brief Implements Prim's algorithm to find the Minimum Spanning Tree (MST) starting from a specified vertex.
     *
     * This function implements Prim's algorithm to find the Minimum Spanning Tree (MST) of the graph,
     * starting from the specified start vertex. It returns the MST as a tour.
     *
     * @Complexity - O(V log V + E)
     *
     * @param start Pointer to the start vertex from which the algorithm begins.
     * @return The Minimum Spanning Tree (MST) represented as a tour.
     */
    Tour prim(Vertex* start);

    /**
     * @brief Recursive helper function for the backtracking algorithm to find the shortest tour.
     *
     * This function is a recursive helper for the backtracking algorithm to find the shortest tour
     * starting from a specified vertex. It explores all possible paths and backtracks when necessary.
     *
     * @complexity - O(V!) in the worst case
     *
     * @param start The starting vertex of the tour.
     * @param min_distance Reference to the minimum distance found so far.
     * @param current_vertex The current vertex being visited.
     * @param current_distance The current distance of the tour.
     * @param path The current path being explored.
     * @param min_path Reference to the path representing the shortest tour found so far.
     * @param is_complete Flag indicating whether the graph is complete.
     */
    void backtrackingHelper(Vertex* start, double& min_distance, Vertex* current_vertex, double current_distance, Tour& path, Tour& min_path, bool is_complete);

    /**
     * @brief Recursive helper function for the Branch and Bound algorithm to find the shortest tour.
     *
     * This function is a recursive helper for the Branch and Bound algorithm to find the shortest tour
     * starting from a specified vertex. It explores all possible paths using backtracking and prunes branches
     * based on a lower bound on the tour length.
     *
     * @complexity - O(V!) in the worst case
     *
     * @param start The starting vertex of the tour.
     * @param min_distance Reference to the minimum distance found so far.
     * @param current_vertex The current vertex being visited in the tour.
     * @param current_distance The current distance of the tour.
     * @param path The current path being explored.
     * @param min_path Reference to the path representing the shortest tour found so far.
     */
    void branchBoundHelper(Vertex* start, double& min_distance, Vertex* current_vertex, double current_distance, Tour& path, Tour& min_path);

    Graph* graph; /**< Graph >**/
    HashTable* vertices_table; /**< Vertices table >**/
};


#endif //TSP_ANALYSIS_CODER_H
