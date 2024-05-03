
#ifndef TSP_ANALYSIS_MANAGER_H
#define TSP_ANALYSIS_MANAGER_H


class Manager {
private:
    double haversine_distance(Vertex* begin, Vertex* end);

public:
    Manager();
    ~Manager();

};


#endif //TSP_ANALYSIS_MANAGER_H
