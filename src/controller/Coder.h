#ifndef TSP_ANALYSIS_CODER_H
#define TSP_ANALYSIS_CODER_H

/**< Project header >**/
#include "HashTable.h"
#include "../model/Graph.h"

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
struct Result {
    vector<Vertex*> path;
    double distance;
    Time time_spent;
};

/**
 * @class Coder - class that contains the algorithms
 */
class Coder {
public:

    /**
     * @constructor Constructor for class Coder
     * @param graph - pointer to graph
     * @param vertices_table - pointer to hashTable
     */
    Coder(Graph* graph, HashTable* vertices_table);

    /**
     * @brief Backtracking algorithm (more used for small graphs)
     * @Complexity -
     * @return Result
     */
    Result backtracking(int start_vertex);

    /**
     * @brief Branch and Bound algorithm (more efficient than backtracking)
     * @Complexity -
     * @return Result
     */
    Result branchBound(int start_vertex);

    /**
     * @brief
     * @Complexity -
     * @return
     */
    Result triangularAproximation(int start_vertex);
    Result held_karp(int start_vertex);
    Result cristofides(int start_vertex);
    Result nearestNeighbor(int start_vertex);
    Result bat_algorithm(int start_vertex);

private:
    void startTimer(timespec& start_real, timespec& start_cpu);
    Time stopTimer(timespec& start_real, timespec& start_cpu, double& elapsed_real, double& elapsed_cpu);
    void backtrackingHelper(Vertex* start, double& min_distance, Vertex* current_vertex, double current_distance, vector<Vertex*>& path, vector<Vertex*>& min_path);
    Graph* graph;
    HashTable* vertices_table;
};


#endif //TSP_ANALYSIS_CODER_H
