#include "Coder.h"
#include <limits>
#include <stack>
#include <random>
#include <cmath>
#include <algorithm>
#include <queue>

void Coder::setNewTable(HashTable* table){
    this->vertices_table = table;
}
void Coder::setNewGraph(Graph* _graph){
    this->graph = _graph;
}

/**
 * @note Distance between two vertices
 */
double Coder::haversineDistance(Vertex* origin, Vertex* destination) {
    try {
        if (origin == nullptr || destination == nullptr) {
            throw CustomError("NullPtr error - origin/destination are null ptr", ERROR);
        }
        Coordinate *originCoord = origin->getCoordinates();
        Coordinate *destinationCoord = destination->getCoordinates();

        if (originCoord == nullptr || destinationCoord == nullptr) {
            throw CustomError("NullPtr error - coordinates are null ptr", ERROR);
        }

        double delta_lat = (destinationCoord->getLatitude() - originCoord->getLatitude()) * M_PI / 180;
        double delta_lon = (destinationCoord->getLongitude() - originCoord->getLongitude()) * M_PI / 180;
        double a = pow(sin(delta_lat / 2), 2) +
                   pow(sin(delta_lon / 2), 2) * cos(originCoord->getLatitude()) * cos(destinationCoord->getLatitude());
        double c = 2 * asin(sqrt(a));
        double d = 6371.0 * c * 1000;
        return d;
    }
    catch (const CustomError& e){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * @note Timer implementation
*/
void Coder::startTimer(timespec& start_real, timespec& start_cpu) {
    clock_gettime(CLOCK_REALTIME, &start_real);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_cpu);
}


Time Coder::stopTimer(timespec& start_real, timespec& start_cpu, double& elapsed_real, double& elapsed_cpu) {
    timespec end_real{}, end_cpu{};

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);
    clock_gettime(CLOCK_REALTIME, &end_real);

    elapsed_real = static_cast<double> (end_real.tv_sec - start_real.tv_sec) +
                   static_cast<double> (end_real.tv_nsec - start_real.tv_nsec) / 1e9;

    elapsed_cpu = static_cast<double> (end_cpu.tv_sec - start_cpu.tv_sec) +
                  static_cast<double> (end_cpu.tv_nsec - start_cpu.tv_nsec) / 1e9;

    return {elapsed_real,elapsed_cpu};

}

/**
 * @note Graph checks
 */
bool Coder::isGraphComplete() {
    try {
        int n = graph->getNumberOfVertexes();
        for (Vertex *v: graph->getVertexSet()) {
            if (v == nullptr) {
                throw CustomError("NullPtr error: vertex v is a nullptr", ERROR);
            }
            int adj_size = 0;
            for (Edge *e: v->getAdj()) {
                if (e == nullptr) {
                    throw CustomError("NullPtr error: edge e is a nullptr", ERROR);
                }
                adj_size++;
            }
            if (adj_size != n - 1) {
                return false;
            }
        }
    }
    catch (const CustomError& e ){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
    return true;
}


bool Coder::isGraphSymmetric(){
    for (Vertex* v : graph->getVertexSet()){
        if (v == nullptr){
            throw CustomError("NullPtr error: vertex v is a nullptr", ERROR);
        }
        for (Edge* e : v->getAdj()){
            if (e == nullptr){
                throw CustomError("NullPtr error: edge e is a nullptr", ERROR);
            }
            bool check = false;
            for (Edge* ed : e->getDestination()->getAdj()){
                if (ed == nullptr){
                    throw CustomError("NullPtr error: edge ed is a nullptr", ERROR);
                }
                if (ed->getDestination() == e->getOrigin()){
                    if (ed->getDistance() == e->getDistance()){
                        check = true;
                    }
                    break;
                }
            }
            if (!check)
                return false;
        }
    }
    return true;
}

/**
  @note Backtracking implementation
 */
void Coder::backtrackingHelper(Vertex* start, double& min_distance, Vertex* current_vertex, double current_distance, Tour& path, Tour& min_path, bool is_complete) {
    if (start == nullptr || current_vertex == nullptr){
        throw CustomError("NullPtr error: vertex current/start is a nullptr", ERROR);
    }
    if (path.size() == graph->getNumberOfVertexes() - 1){
        double distance_to_origin;
        bool findCycle = false;
        for (Edge* e : current_vertex->getAdj()){
            if (e == nullptr){
                throw CustomError("NullPtr error: edge e is a nullptr", ERROR);
            }
            if (e->getDestination()->getId() == start->getId()){
                distance_to_origin = e->getDistance();
                path.push_back(e);
                findCycle = true;
                break;
            }
        }

        if (!findCycle){
            if (!is_complete) {
                if (current_vertex->getCoordinates() != nullptr && start->getCoordinates() != nullptr) {
                    distance_to_origin = haversineDistance(current_vertex, start);
                    Edge* e = graph->addEdge(current_vertex, start, distance_to_origin);
                    path.push_back(e);
                }
                else{
                    return;
                }
            }
            else{
                return;
            }
        }

        double total_distance = current_distance + distance_to_origin;
        if (total_distance < min_distance){
            min_distance = total_distance;
            min_path.assign(path.begin(), path.end());
        }
        path.pop_back();
        return;
    }
    vector<Vertex*> connected;
    for (Edge* e : current_vertex->getAdj()){
        connected.push_back(e->getDestination());
        Vertex* destination = e->getDestination();
        if (destination == nullptr){
            throw CustomError("NullPtr error: vertex v is a nullptr", ERROR);
        }

        if (!destination->isVisited()){
            destination->setVisited(true);
            current_distance+= e->getDistance();
            path.push_back(e);

            backtrackingHelper(start,min_distance,destination,current_distance,path,min_path,is_complete);

            destination->setVisited(false);
            current_distance-= e->getDistance();
            path.pop_back();
        }
    }
    if (!is_complete) {
        for (Vertex *v: graph->getVertexSet()) {
            if (!v->isVisited() && find(connected.begin(), connected.end(), v) == connected.end()) {
                if (current_vertex->getCoordinates() == nullptr || v->getCoordinates() == nullptr) {
                    continue;
                }
                double haversine_dist = haversineDistance(current_vertex, v);
                Edge *new_edge = graph->addEdge(current_vertex, v, haversine_dist);
                current_distance += haversine_dist;
                path.push_back(new_edge);
                v->setVisited(true);

                backtrackingHelper(start, min_distance, v, current_distance, path, min_path, is_complete);

                v->setVisited(false);
                current_distance -= haversine_dist;
                path.pop_back();
            }
        }
    }
}



Result Coder::backtracking(int start_vertex) {
    // Initialize Timer
    timespec start_real{};
    timespec start_cpu{};
    double elapsed_real, elapsed_cpu;
    startTimer(start_real, start_cpu);
    bool is_complete = isGraphComplete();

    // Set all vertex to visited false
    for (Vertex *v: graph->getVertexSet()) {
        if (v == nullptr) {
            throw CustomError("NullPtr: vertex v is a null ptr", ERROR);
        }
        v->setVisited(false);
    }

    // Initialize distance
    double min_distance = numeric_limits<double>::max();

    // Start vertex (visited)
    Vertex *start = vertices_table->search(start_vertex);
    if (start == nullptr) {
        throw CustomError("NullPtr: vertex start is a null ptr", ERROR);
    }
    start->setVisited(true);

    // Path
    Tour min_path;
    Tour path;

    // Backtracking calculation
    backtrackingHelper(start, min_distance, start, 0, path, min_path,is_complete);


    // Finish Timer
    Time t = stopTimer(start_real, start_cpu, elapsed_real, elapsed_cpu);
    return {min_path, min_distance, t};
}

/**
 * @note Branch-bound implementation
 */
void Coder::branchBoundHelper(Vertex* start, double& min_distance, Vertex* current_vertex, double current_distance, Tour& path, Tour& min_path) {
    if (start == nullptr || current_vertex == nullptr){
        throw CustomError("NullPtr error: vertex current/start is a nullptr", ERROR);
    }
    if (path.size() == graph->getNumberOfVertexes() - 1){
        double distance_to_origin;
        bool findCycle = false;
        for (Edge* e : current_vertex->getAdj()){
            if (e == nullptr){
                throw CustomError("NullPtr error: edge e is a nullptr", ERROR);
            }
            if (e->getDestination()->getId() == start->getId()){
                distance_to_origin = e->getDistance();
                path.push_back(e);
                findCycle = true;
                break;
            }
        }

        if (!findCycle){
            return;
        }

        double total_distance = current_distance + distance_to_origin;
        if (total_distance < min_distance){
            min_distance = total_distance;
            min_path.assign(path.begin(), path.end());
        }
        path.pop_back();
        return;
    }

    for (Edge* e : current_vertex->getAdj()){
        if (e == nullptr){
            throw CustomError("NullPtr error: edge e is a nullptr", ERROR);
        }
        Vertex* destination = e->getDestination();
        if (destination == nullptr){
            throw CustomError("NullPtr error: vertex v is a nullptr", ERROR);
        }

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
    startTimer(start_real, start_cpu);

    // Set all vertex to visited false
    for (Vertex *v: graph->getVertexSet()) {
        if (v == nullptr) {
            throw CustomError("NullPtr: vertex v is a null ptr", ERROR);
        }

        v->setVisited(false);
    }

    // Initialize distance
    double min_distance = numeric_limits<double>::max();

    // Start vertex (visited)
    Vertex *start = vertices_table->search(start_vertex);
    if (start == nullptr) {
        throw CustomError("NullPtr: vertex start is a null ptr", ERROR);
    }
    start->setVisited(true);

    // Path
    Tour min_path;
    Tour path;

    // Backtracking calculation
    branchBoundHelper(start, min_distance, start, 0, path, min_path);

    // Finish Timer
    Time t = stopTimer(start_real, start_cpu, elapsed_real, elapsed_cpu);
    return {min_path, min_distance, t};
}



/**
 * @note Lin Khernigan implementation
 */

double Coder::calculateTourCost(const Tour& tour){
    double tour_cost = 0.0;
    for (Edge* e : tour){
       tour_cost += e->getDistance();
    }
    return tour_cost;
}

Result Coder::cristofides(int start_vertex) {
    return {};
}

void Coder::preOrderVisit(Vertex *current, vector<Vertex*>& t) {
    for (Edge* e : current->getAdj()){
        if (e->getDestination()->getPath() == e  && !e->getDestination()->isVisited()){
            t.push_back(e->getDestination());
            e->getDestination()->setVisited(true);
            preOrderVisit(e->getDestination(),t);

        }
    }
}

struct Comparator {
    bool operator()(Vertex* a, Vertex* b) {
        return a->getKey() > b->getKey();
    }
};


Tour Coder::prim(Vertex* start) {
    // Initialization
    double max = numeric_limits<double>::max();
    priority_queue<Vertex *, vector<Vertex *>, Comparator> pq;

    // Mst initial values
    for (Vertex *v: graph->getVertexSet()) {
        if (v == nullptr) {
            throw CustomError("Null Ptr: vertex v is a null ptr", ERROR);
        }
        v->setVisited(false);
        v->setKey(max);
    }

    start->setKey(0);
    pq.push(start);

    // Calculate mst
    while (!pq.empty()) {
        Vertex *v = pq.top();
        pq.pop();
        if (v->isVisited()) continue;
        v->setVisited(true);

        // First do a normal search, then calculate every distance to another edge if graph have coordinates.
        if (!v->getAdj().empty()) {
            for (Edge *e: v->getAdj()) {
                if (!e->getDestination()->isVisited() && e->getDistance() < e->getDestination()->getKey()) {
                    e->getDestination()->setKey(e->getDistance());
                    e->getDestination()->setPath(e);
                    pq.push(e->getDestination());
                }
            }
        }
        // Do search in prim with haversine
        else {
            for (Vertex *v1: graph->getVertexSet()) {
                if (!v1->isVisited()) {
                    if (v->getCoordinates() == nullptr || v1->getCoordinates() == nullptr){
                        continue;
                    }
                    double distance = haversineDistance(v, v1);
                    if (distance < v1->getKey()) {
                        Edge* e = graph->addEdge(v, v1, distance);
                        v1->setKey(distance);
                        v1->setPath(e);
                        pq.push(v1);
                    }
                }
            }
        }
    }

    // Visit mst in pre-order visit
    for (Vertex* v : graph->getVertexSet()){
        if (v == nullptr){
            throw CustomError("Null Ptr: vertex v is a null ptr",ERROR);
        }
        v->setVisited(false);
    }
    vector<Vertex*> mst_v;
    start->setVisited(true);
    mst_v.push_back(start);
    preOrderVisit(start,mst_v);
    // Check if mst_v is a spanning tree
    cout << mst_v.size() << endl;

    // Get the mst (convert vector<Vertex*> to Tour)
    Tour mst;
    for (int i = 0; i < mst_v.size() - 1; i++){
        Vertex* origin = mst_v[i];
        Vertex* destination = mst_v[i+1];
        if (origin == nullptr || destination == nullptr){
            throw CustomError("Null Ptr: origin/destination is a null ptr",ERROR);
        }
        bool find = false;
        for (Edge* e : origin->getAdj()) {
            if (e == nullptr){
                throw CustomError("Null Ptr: edge is a null ptr",ERROR);
            }
            if (e->getDestination() == destination) {
                find = true;
                mst.push_back(e);
                break;
            }
        }
        if (!find){
            if (origin->getCoordinates() != nullptr || destination->getCoordinates() != nullptr) {
                double distance = haversineDistance(origin, destination);
                Edge *e = graph->addEdge(origin, destination, distance);
                mst.push_back(e);
            }
        }
    }
    return mst;
}


Result Coder::triangularApproximation(int start_vertex) {
    // Start timer
    timespec start_real{};
    timespec start_cpu{};
    double elapsed_real, elapsed_cpu;
    startTimer(start_real, start_cpu);

    // Find first vertex
    Vertex* start = vertices_table->search(start_vertex);
    if (start == nullptr){
        throw CustomError("Null Ptr: start vertex is a null ptr",ERROR);
    }

    // Find mst
    Tour mst = prim(start);

    // If mst is empty, there is no path found
    if (mst.empty()){
        Time time = stopTimer(start_real,start_cpu,elapsed_real,elapsed_cpu);
        return {mst,0,time};
    }

    // The result could be an invalid spanning tree.
    cout << mst.size() << endl;
    if (mst.size() != graph->getNumberOfVertexes()-1){
        return {};
    }

    for (Vertex* v : graph->getVertexSet()){
        v->setVisited(false);
    }

    for (Edge* e : mst){
        if (e->getOrigin()->isVisited()){
            return {};
        }
        e->getOrigin()->setVisited(true);
    }
    Vertex* last_vertex = mst.back()->getDestination();
    if (last_vertex->isVisited()){
        return {};
    }
    last_vertex->setVisited(true);

    for (Vertex* v : graph->getVertexSet()){
        if (!v->isVisited()){
            return {};
        }
        v->setVisited(false);
    }

    bool findEdge = false;
    // Find edge for completing the cycle
    for (Edge* e : last_vertex->getAdj()){
        if (e == nullptr){
            throw CustomError("Null Ptr: edge is a null ptr",ERROR);
        }
        if (e->getDestination() == start){
            findEdge = true;
            mst.push_back(e);
            break;
        }
    }

    // If there is no edge try using coordinates
    if (!findEdge){
        if (last_vertex->getCoordinates() == nullptr || start->getCoordinates() == nullptr){
            return {};
        }
        else{
            double distance = haversineDistance(last_vertex,start);
            Edge* cycle_edge = graph->addEdge(last_vertex,start,distance);
            mst.push_back(cycle_edge);
        }
    }

    // Get the result
    double distance = 0.0;
    for (Edge* e : mst){
        distance += e->getDistance();
    }

    // Finish timer
    Time time = stopTimer(start_real,start_cpu,elapsed_real,elapsed_cpu);
    return {mst,distance,time};
}

Result Coder::realWorld(int start_vertex) {
    return {};
}




