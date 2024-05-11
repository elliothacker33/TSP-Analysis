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


void Coder::buildInitialRandomTour(Tour& initialTour, int start_vertex) {

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

    for (int i = 0; i < shuffledVertices.size() - 1; i++){
        Vertex* v1 = shuffledVertices[i];
        Vertex* v2 = shuffledVertices[i+1];
        e = graph->getEdgeFromGraph(v1,v2);
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


Tour Coder::unionEdgesTourTrail(const Tour& tour, const Tour& trail) {
    Tour union_tour;

    for (auto e : tour) {
        if (find(union_tour.begin(), union_tour.end(), e) == union_tour.end()) {
            union_tour.push_back(e);
        }
    }

    for (auto e : trail) {
        if (find(union_tour.begin(), union_tour.end(), e) == union_tour.end()) {
            union_tour.push_back(e);
        }
    }

    return union_tour;
}

bool Coder::isHamiltonian(const Tour& t){
    // Check empty
    return true;



}

Tour Coder::differenceTour(const Tour& t1, const Tour& t2) {
    Tour diff_tour;

    for (auto e : t1) {
        if (find(t2.begin(), t2.end(), e) == t2.end() && find(diff_tour.begin(),diff_tour.end(),e) == diff_tour.end()) {
            diff_tour.push_back(e);
        }
    }
    for (auto e : t2) {
        if (find(t1.begin(), t1.end(), e) == t1.end() && find(diff_tour.begin(),diff_tour.end(),e) == diff_tour.end()) {
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

        buildInitialRandomTour(tour, start_vertex);
        stack<KherniganCell> st;
        double gStar;
        do {
            for (auto v: graph->getVertexSet()) {
                st.push({v, 0, 0});
            }
            gStar = 0.0;
            Tour currentTrail;
            Vertex* v0 = nullptr;
            while(!st.empty()){
                KherniganCell currCell = st.top();
                st.pop(); // Done
                if (currCell.i == 0){
                    v0 = currCell.v;
                }
                if (currCell.i % 2 == 0){
                    for (Edge* e : currCell.v->getAdj()){

                        if (!edgeAlreadyOnTour(e,currentTrail) && edgeAlreadyOnTour(e,tour)){
                            Vertex* u = e->getDestination();
                            Edge* cycle_edge = graph->getEdgeFromGraph(u,v0);

                            currentTrail.push_back(e);
                            Tour unionTour = unionEdgesTourTrail(tour,currentTrail);
                            currentTrail.push_back(cycle_edge);

                            Tour symmetricTour = differenceTour(tour,currentTrail);
                            currentTrail.pop_back();
                            currentTrail.pop_back();


                            if (currCell.i <= p2 || (!edgeAlreadyOnTour(cycle_edge,unionTour) && isHamiltonian(symmetricTour))){
                                st.push({u,currCell.i + 1,currCell.g + e->getDistance()});
                            }

                        }
                    }
                }

                else{
                    Edge* e = graph->getEdgeFromGraph(currCell.v,v0);
                    currentTrail.push_back(e);
                    Tour symmetric_tour = differenceTour(tour,currentTrail);
                    currentTrail.pop_back();

                    if (currCell.g > e->getDistance() && currCell.g - e->getDistance() > gStar && isHamiltonian(symmetric_tour)){
                        currentTrail.push_back(e);
                        gStar = currCell.g - e->getDistance();

                        for (Edge* e1 : currCell.v->getAdj()){
                            Vertex* u = e1->getDestination();
                            currentTrail.pop_back();
                            Tour union_tour = unionEdgesTourTrail(tour,currentTrail);
                            currentTrail.push_back(e);

                            if (currCell.g > e1->getDistance() && !edgeAlreadyOnTour(e1,union_tour)){
                                st.push({u,currCell.i + 1, currCell.g - e1->getDistance()});
                            }
                        }
                    }
                }

                KherniganCell topNow = st.top();
                if (currCell.i <= topNow.i){
                    if (gStar > 0){
                        tour = differenceTour(tour,currentTrail);
                    }
                    else if (currCell.i > p1){
                        stack<KherniganCell> tmpStack;
                        // Reset stack
                        while(!st.empty()){
                            KherniganCell t = st.top();
                            if (t.i <= p1){
                                tmpStack.push(t);
                            }
                            st.pop();
                        }
                        while (!tmpStack.empty()){
                            st.push(tmpStack.top());
                            tmpStack.pop();
                        }
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
    priority_queue<Vertex*, vector<Vertex*>, Comparator> pq;

    for (Vertex* v : graph->getVertexSet()){
        v->setVisited(false);
        v->setPath(nullptr);
        v->setKey(max);
    }

    start->setKey(0);
    pq.push(start);
    while(!pq.empty()){
        Vertex* v = pq.top();
        pq.pop();
        if (v->isVisited()) continue;
            v->setVisited(true);
        for (Edge* e : v->getAdj()){
            if(!e->getDestination()->isVisited() && e->getDistance() < e->getDestination()->getKey()){
                e->getDestination()->setKey(e->getDistance());
                e->getDestination()->setPath(e);
                pq.push(e->getDestination());
            }
        }
    }

    // Get the result of MST
    Tour mst;
    for (Vertex* v : graph->getVertexSet()){
        v->setVisited(false);
    }
    vector<Vertex*> v;
    start->setVisited(true);
    v.push_back(start);
    preOrderVisit(start,v);
    for (int i = 0; i < v.size() -1 ; i++){
        Vertex* origin = v[i];
        Vertex* destination = v[i+1];
        for (Edge* e : origin->getAdj()) {
            if (e->getDestination() == destination) {
                mst.push_back(e);
                break;
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

    // Build MST
    Vertex* start = vertices_table->search(start_vertex);
    Tour t = prim(start);

    // Add cycle edge
    Vertex* last_v = t.back()->getDestination();
    for (Edge* e : last_v->getAdj()){
        if (e->getDestination() == start){
            t.push_back(e);
            break;
        }
    }

    // Get the result
    double distance = 0.0;
    for (Edge* e : t){
        distance += e->getDistance();
    }

    // Finish timer
    Time time = stopTimer(start_real,start_cpu,elapsed_real,elapsed_cpu);
    return {t,distance,time};
}

Result Coder::realWorld(int start_vertex) {
    return {};
}

Result Coder::held_karp(int start_vertex) {
    return {};
}



