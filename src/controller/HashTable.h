#ifndef TSP_ANALYSIS_HASHTABLE_H
#define TSP_ANALYSIS_HASHTABLE_H

/**
 * @file HashTable.h - This is the header file for our hashtable.
 * @note We changed from unordered map to this, because we have better control on our own implementation.
 * @remark This implementation only works for HashBucket but can be changed to work with templates.
 */

/**<Project headers >**/
#include "../model/Vertex.h"

/**
 * @class HashBucket - This buckets contain an id for key and Vertex for value
 */
class HashBucket{
public:
    /**
     * @constructor Constructor for HashBucket
     * @param _id - id for identification
     * @param _vertex - pointer to vertex
     */
    HashBucket(int _id , Vertex* _vertex) : id(_id), vertex(_vertex) {};

    /**
     * @brief Equal operator to compare buckets
     * @param bucket - reference to another bucket
     * @return true if equal buckets else false
     */
    bool operator==(const HashBucket& bucket) const;

    /**
     * @brief Get identification of this hash bucket (key)
     * @return id
     */
    [[nodiscard]] int getId() const;

    /**
     * @brief Get vertex (value)
     * @return
     */
    [[nodiscard]] Vertex* getVertex() const;
private:
    int id; /**< identification >**/
    Vertex* vertex; /**< pointer to vertex >**/
};

/**
 * @class HashTable - table to access vertices by their id
 */
class HashTable {
public:
    /**
     * @destructor HashTable destructor
     */
    ~HashTable();

    /**
     * @constructor HashTable constructor
     * @param real_capacity - number of vertices in the dataset
     */
    explicit HashTable(int real_capacity);

    /**
     * @brief This method builds an hash for vertex
     * @param id - identification
     * @return hash for identification of a vertex
     */
    [[nodiscard]] int getHash(int id) const;

    /**
     * @brief Check if hashTable is empty or not
     * @return true if the hashTable is empty else false
     */
    [[nodiscard]] bool isEmpty() const;

    /**
     * @brief Get size of elements inserted on the hashTable
     * @return hashTable
     */
    [[nodiscard]] int getSize() const;

    /**
     * @brief Insert bucket into hashTable
     * @param _id - identification of a vertex
     * @param _vertex - pointer to vertex
     */
    void insertBucket(int _id, Vertex* _vertex);

    /**
     * @bried Remove bucket from hashTable
     * @param _id - identification of a vertex
     */
    void deleteBucket(int _id);

    /**
     * @brief Get the vertex associated with an id
     * @param _id - identification of a vertex
     * @return - pointer to vertex
     */
    Vertex* search(int _id);

private:
    HashBucket* dummy; /**< Dummy Bucket used for deleting purposes >**/
    HashBucket** table; /**< Table with all the buckets >**/
    int capacity; /**< Capacity of the table >**/
    int size = 0; /**< Number of buckets in the table >**/

};


#endif //TSP_ANALYSIS_HASHTABLE_H
