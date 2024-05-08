#ifndef TSP_ANALYSIS_CODER_H
#define TSP_ANALYSIS_CODER_H

/**< Project header >**/
#include "HashTable.h"
#include "../model/Graph.h"
#include "../Exceptions/CustomError.h"

struct KherniganCell{
    Vertex* v; /**< Current vertex >**/
    int i; /**< Current number of edges in trail >**/
    double g; /**< Current trail gain >**/
};

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
     * @Complexity -
     * @return Result
     */
    Result backtracking(int start_vertex = 0);

    /**
     * @brief Branch and Bound algorithm (more efficient than backtracking)
     * @Complexity -
     * @return Result
     */
    Result branchBound(int start_vertex = 0);

    /**
     * @brief
     * @Complexity -
     * @return
     */
    Result triangularAproximation(int start_vertex = 0);
    Result held_karp(int start_vertex = 0);
    Result cristofides(int start_vertex = 0);
    Result nearestNeighbor(int start_vertex = 0);
    Result linKhernigan(int start_vertex = 0);
    Result realWorld(int start_vertex = 0);



private:
    static void startTimer(timespec& start_real, timespec& start_cpu);
    static Time stopTimer(timespec& start_real, timespec& start_cpu, double& elapsed_real, double& elapsed_cpu);
    bool isGraphComplete();
    bool isGraphSymmetric();
    double calculateTourCost(const Tour& tour);
    void buildInitialRandomTour(Tour &initialTour, int start_vertex);
    bool edgeAlreadyOnTour(Edge* e, Tour& t);
    bool isHamiltonian(const Tour& t);
    static double haversineDistance(Vertex* origin, Vertex* destination);
    Tour unionEdgesTourTrail(const Tour& t, const Tour& trail_converted);
    Tour differenceTour(const Tour& t1, const Tour& t2);
    void backtrackingHelper(Vertex* start, double& min_distance, Vertex* current_vertex, double current_distance, Tour& path, Tour& min_path);
    void branchBoundHelper(Vertex* start, double& min_distance, Vertex* current_vertex, double current_distance, Tour& path, Tour& min_path);
    Graph* graph;
    HashTable* vertices_table;
};


#endif //TSP_ANALYSIS_CODER_H
