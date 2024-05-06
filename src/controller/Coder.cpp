#include "Coder.h"
#include <limits>

Coder::Coder(Graph *graph, HashTable *vertices_table) {
    this->graph = graph;
    this->vertices_table = vertices_table;
}
void Coder::startTimer(timespec& start_real, timespec& start_cpu) {
    clock_gettime(CLOCK_REALTIME, &start_real);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_cpu);
}

Time Coder::stopTimer(timespec& start_real, timespec& start_cpu, double& elapsed_real, double& elapsed_cpu) {
    timespec end_real{}, end_cpu{};

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);
    clock_gettime(CLOCK_REALTIME, &end_real);

    elapsed_real = (end_real.tv_sec - start_real.tv_sec) +
                   (end_real.tv_nsec - start_real.tv_nsec) / 1e9;

    elapsed_cpu = (end_cpu.tv_sec - start_cpu.tv_sec) +
                  (end_cpu.tv_nsec - start_cpu.tv_nsec) / 1e9;

    return {elapsed_real,elapsed_cpu};

}
void Coder::backtrackingHelper(Vertex* start, double& min_distance, Vertex* current_vertex, double current_distance, vector<Vertex*>& path, vector<Vertex*>& min_path) {
    if (path.size() == graph->getNumberOfVertexes()){
        path.push_back(start);
        double distance_to_origin;
        for (Edge* e : current_vertex->getAdj()){
            if (e->getDestination()->getId() == start->getId()){
                distance_to_origin = e->getDistance();
                break;
            }
        }

        double total_distance = current_distance + distance_to_origin;
        if (total_distance< min_distance){
            min_distance = total_distance;
            min_path.assign(path.begin(), path.end());
        }
        path.pop_back();
        return;
    }

    for (Edge* e : current_vertex->getAdj()){
        // Not visited
        Vertex* destination = e->getDestination();
        if (!destination->isVisited()){
            destination->setVisited(true);
            current_distance+= e->getDistance();
            path.push_back(destination);

            backtrackingHelper(start,min_distance,destination,current_distance,path,min_path);

            destination->setVisited(false);
            current_distance-= e->getDistance();
            path.pop_back();
        }
    }
}

Result Coder::backtracking(int start_vertex) {
    // Initialize Timer
    timespec start_real{};
    timespec start_cpu{};
    double elapsed_real, elapsed_cpu;
    startTimer(start_real,start_cpu);

    // Set all vertex to visited false
    for (Vertex* v : graph->getVertexSet()){
        v->setVisited(false);
    }

    // Initialize distance
    double min_distance = numeric_limits<double>::max();

    // Start vertex (visited)
    Vertex* start = vertices_table->search(start_vertex);
    start->setVisited(true);

    // Path
    vector<Vertex*> min_path;
    vector<Vertex*> path;
    path.push_back(start);

    // Backtracking calculation
    backtrackingHelper(start,min_distance,start,0,path,min_path);

    // Finish Timer
    Time t = stopTimer(start_real,start_cpu,elapsed_real,elapsed_cpu);
    return {min_path,min_distance,t};

}

Result Coder::branchBound(int start_vertex) {

}