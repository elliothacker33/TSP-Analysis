//
// Created by tomas on 03-05-2024.
//

#ifndef TSP_ANALYSIS_GRAPH_H
#define TSP_ANALYSIS_GRAPH_H

class Vertex;

class Edge {
public:
    Edge(Vertex* orig, Vertex* dest, double distance);
    double getDistance() const;
    Vertex* getDestination() const;
    Vertex* getOrigin() const;
    Edge* getReverseEdge() const;
    void setReverseEdge();
private:
    Vertex* origin;
    Vertex* destination;
    double distance;
    Edge* reverse = nullptr;

};

class Vertex {

};

class Graph {
public:
    ~Graph();
    vector<Vertex*> getVertexSet() const;
    int getNumberOfVertexes() const;
    bool addVertex(Vertex* v);
    void removeVertex(Vertex* v);
    void removeEdge(const Edge* e);
    Edge* addEdge(Vertex* orig, Vertex* dest, int capacity, const string& type);
    static string getCode(Vertex* v);
    static string getName(Vertex* v);

protected:
    vector<Vertex*> vertexSet;
    int n = 0;
};



#endif //TSP_ANALYSIS_GRAPH_H
