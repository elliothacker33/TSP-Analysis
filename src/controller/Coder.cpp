#include "Coder.h"
#include <limits>
#include <stack>
#include <random>
#include <algorithm>

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
bool Coder::isGraphComplete(){
    int n = graph->getNumberOfVertexes();
    for (Vertex* v: graph->getVertexSet()){
        if (v->getAdj().size() != n-1){
            return false;
        }
    }
    return true;
}

bool Coder::isGraphSymmetric(){
    for (Vertex* v : graph->getVertexSet()){
        for (Edge* e : v->getAdj()){
            bool check = false;
            for (Edge* ed : e->getDestination()->getAdj()){
                if (ed->getDestination() == e->getOrigin() && ed->getDistance() == e->getDistance()){
                    check = true;
                    break;
                }
            }
            if (!check)
                return false;
        }
    }
    return true;
}

void Coder::backtrackingHelper(Vertex* start, double& min_distance, Vertex* current_vertex, double current_distance, Tour& path, Tour& min_path) {
    if (path.size() == graph->getNumberOfVertexes()){

        double distance_to_origin;
        for (Edge* e : current_vertex->getAdj()){
            if (e->getDestination()->getId() == start->getId()){
                distance_to_origin = e->getDistance();
                path.push_back(e);
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
            path.push_back(e);

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
    Tour min_path;
    Tour path;

    // Backtracking calculation
    backtrackingHelper(start,min_distance,start,0,path,min_path);

    // Finish Timer
    Time t = stopTimer(start_real,start_cpu,elapsed_real,elapsed_cpu);
    return {min_path,min_distance,t};

}

void Coder::branchBoundHelper(Vertex* start, double& min_distance, Vertex* current_vertex, double current_distance, Tour& path, Tour& min_path) {
    if (path.size() == graph->getNumberOfVertexes()){
        double distance_to_origin;
        for (Edge* e : current_vertex->getAdj()){
            if (e->getDestination()->getId() == start->getId()){
                distance_to_origin = e->getDistance();
                path.push_back(e);
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
        if (!destination->isVisited() && current_distance + e->getDistance() < min_distance){
            destination->setVisited(true);
            current_distance+= e->getDistance();
            path.push_back(e);

            branchBoundHelper(start,min_distance,destination,current_distance,path,min_path);

            destination->setVisited(false);
            current_distance-= e->getDistance();
            path.pop_back();
        }
    }
}

Result Coder::branchBound(int start_vertex) {
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
    Tour min_path;
    Tour path;

    // Backtracking calculation
    branchBoundHelper(start,min_distance,start,0,path,min_path);

    // Finish Timer
    Time t = stopTimer(start_real,start_cpu,elapsed_real,elapsed_cpu);
    return {min_path,min_distance,t};
}



double Coder::calculateTourCost(const Tour& tour){
    double tour_cost = 0.0;
    for (Edge* e : tour){
       tour_cost += e->getDistance();
    }
    return tour_cost;
}




void Coder::buildInitialRandomTour(int start_vertex, Tour& initialTour) {

    vector<Vertex*> shuffledVertices;
    for (auto v : graph->getVertexSet()){
        if (v->getId() != start_vertex){
            shuffledVertices.push_back(v);
        }
    }

    auto rd = random_device {};
    auto rng = default_random_engine { rd() };
    shuffle(shuffledVertices.begin(), shuffledVertices.end(), rng);

    Vertex* start = vertices_table->search(start_vertex);
    Vertex* next_start = shuffledVertices[0];
    Edge* e = graph->getEdgeFromGraph(start,next_start);
    initialTour.push_back(e);

    for (int i = 1; i < shuffledVertices.size() - 1; i++){
        Vertex* v1 = shuffledVertices[i];
        Vertex* v2 = shuffledVertices[i+1];
        e = graph->getEdgeFromGraph(start,next_start);
        initialTour.push_back(e);
    }

    Vertex* before_finish = shuffledVertices[shuffledVertices.size()-1];
    e = graph->getEdgeFromGraph(before_finish,start);
    initialTour.push_back(e);

}

bool Coder::edgeAlreadyOnTour(Edge* e, Tour& t){
    for (auto edge : t ){
        if (edge == e){
            return true;
        }
    }
    return false;
}

Tour Coder::convertTrailToTour(vector<Vertex*> trail){
    Tour t;
    for (int i = 0; i < trail.size()-1; i++){
        Vertex* v1 = trail[i];
        Vertex* v2 = trail[i+1];
        Edge* edge = graph->getEdgeFromGraph(v1,v2);
        t.push_back(edge);
    }
    Edge* edge = graph->getEdgeFromGraph(trail[trail.size()-1],trail[0]);
    t.push_back(edge);
    return t;
}

Tour Coder::unionEdgesTourTrail(const Tour& t, const Tour& trail_converted) {
    Tour union_tour;

    for (auto e : t) {
        if (find(union_tour.begin(), union_tour.end(), e) == union_tour.end()) {
            union_tour.push_back(e);
        }
    }

    for (auto e : trail_converted) {
        if (find(union_tour.begin(), union_tour.end(), e) == union_tour.end()) {
            union_tour.push_back(e);
        }
    }

    return union_tour;
}

bool Coder::isHamiltonian(const Tour& t){
    // Check empty
    if (t.empty()){
        return false;
    }

    for (auto to)

    // Check first and last
    if (t.back() != t.front()){
        return false;
    }



}

Tour Coder::differenceTour(const Tour& t1, const Tour& t2) {
    Tour diff_tour;

    for (auto e : t1) {
        if (find(t2.begin(), t2.end(), e) != t2.end()) {
            diff_tour.push_back(e);
        }
    }
    for (auto e : t2) {
        if (find(t1.begin(), t1.end(), e) != t1.end()) {
            diff_tour.push_back(e);
        }
    }

    return diff_tour;
}


Result Coder::linKhernigan(int start_vertex){

    if (isGraphSymmetric() && isGraphComplete()) {
        timespec start_real{};
        timespec start_cpu{};
        double elapsed_real, elapsed_cpu;
        startTimer(start_real, start_cpu);

        int p1 = 5;
        int p2 = 2;
        Tour tour;

        buildInitialRandomTour(start_vertex, tour);
        double initialCost = calculateTourCost(tour);
        stack<KherniganCell> st;
        double gStar;
        do {
            vector<Edge*> best_edges_to_change;
            for (auto v: graph->getVertexSet()) {
                st.push({v, 0, 0});
            }
            gStar = 0.0;
            vector<Vertex*> currentTrail;

            while(!st.empty()){
                KherniganCell currCell = st.top();
                st.pop();
                currentTrail.push_back(currCell.v);

                if (currCell.i % 2 == 0){
                    Tour trail_converted = convertTrailToTour(currentTrail);
                    for (Vertex* v : graph->getVertexSet()){
                        Edge* e = graph->getEdgeFromGraph(currCell.v,v);
                        if (!edgeAlreadyOnTour(e,trail_converted) && edgeAlreadyOnTour(e,tour)){
                            trail_converted.push_back(e);
                            Tour union_edges = unionEdgesTourTrail(tour,trail_converted);
                            Vertex* trail_begin = currentTrail[0]; // Used for cycle check
                            Edge* e_cycle = graph->getEdgeFromGraph(v,trail_begin);
                            trail_converted.push_back(e_cycle);
                            Tour symmetric_difference_edges = differenceTour(tour,trail_converted);

                            if (currCell.i <= 2 || (!edgeAlreadyOnTour(e_cycle,union_edges) && isHamiltonian(symmetric_difference_edges))){
                                st.push({v,currCell.i + 1,currCell.g + e->getDistance()});
                            }

                        }
                    }
                }
                else{
                    Tour trail_converted = convertTrailToTour(currentTrail);
                    Edge* e = graph->getEdgeFromGraph(currCell.v,currentTrail[0]);
                    trail_converted.push_back(e);
                    Tour symmetric_difference_edges = differenceTour(tour,trail_converted);

                    if (currCell.g > e->getDistance() && currCell.g - e->getDistance() > gStar && isHamiltonian(symmetric_difference_edges)){
                        best_edges_to_change = trail_converted;
                        gStar = currCell.g - e->getDistance();
                        for (auto v : graph->getVertexSet()){
                            Edge* edge = graph->getEdgeFromGraph(currCell.v,v);
                            trail_converted.pop_back();
                            Tour union_edges = unionEdgesTourTrail(tour,trail_converted);
                            if (currCell.g > edge->getDistance() && !edgeAlreadyOnTour(edge,union_edges)){
                                st.push({v,currCell.i + 1, currCell.g - edge->getDistance()});
                            }
                        }
                    }
                }
                KherniganCell topNow = st.top();
                if (currCell.i <= topNow.i){
                    if (gStar > 0){
                        tour = differenceTour(tour,best_edges_to_change);
                    }
                    else if (currCell.i > p1){
                        // reshapeStack()
                    }
                }

            }

        }
        while(gStar != 0); // While gStar can be improved keep doing the algorithm.

        double tourCost = calculateTourCost(tour);
        Time t = stopTimer(start_real,start_cpu,elapsed_real,elapsed_cpu);
        return {tour,tourCost,t};
    }
    else{
        throw CustomError("Lin khernigan only works for complete and symmetric graphs", SEMANTIC_ERROR);
    }
}





