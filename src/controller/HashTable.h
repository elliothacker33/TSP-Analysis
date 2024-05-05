#ifndef TSP_ANALYSIS_HASHTABLE_H
#define TSP_ANALYSIS_HASHTABLE_H

/**<Project headers >**/
#include "../model/Vertex.h"

class HashBucket{
public:
    HashBucket(int _id , Vertex* _vertex) : id(_id), vertex(_vertex) {};
    bool operator==(const HashBucket& bucket) const;
    [[nodiscard]] int getId() const;
    [[nodiscard]] Vertex* getVertex() const;
private:
    int id;
    Vertex* vertex;
};

class HashTable {
public:
    ~HashTable();
    explicit HashTable(int real_capacity);
    [[nodiscard]] int getHash(int id) const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] int getSize() const;
    void insertBucket(int _id, Vertex* _vertex);
    void deleteBucket(int _id);
    Vertex* search(int _id);
    HashBucket* dummy; // Used for deletion purposes
private:
    HashBucket** table;
    int capacity;
    int size = 0;

};


#endif //TSP_ANALYSIS_HASHTABLE_H
