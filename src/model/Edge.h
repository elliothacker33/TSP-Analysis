#ifndef TSP_ANALYSIS_EDGE_H
#define TSP_ANALYSIS_EDGE_H

/**
* @file Edge.h
* @brief This file contains the Edge header.
*/

/**
 * @note [[nodiscard]] forces the coder to use the values returned to avoid leaks.
 */

class Vertex;

/**
 * @class Edge
 * @brief Represents a edge that connects two vertexes in a graph.
 *
 * This class represents a pipe in the context of the problem, and is represented by two pointer, to the origin vertex
 * and destination vertex, capacity and type of the edge.
 */
class Edge {
public:

    // Overloading < operator
    bool operator<(const Edge& obj) const
    {
        return distance < obj.getDistance();
    }

    /**
     * @brief Constructs an edge between two locations with an origin-destination with a distance.
     * @param origin - Pointer to the origin vertex
     * @param destination - Pointer to the destination vertex
     * @param distance - Distance between origin and destination
     */
    Edge(Vertex* orig, Vertex* dest, double distance);

    /**
     * @brief Distance between two vertices
     * @return distance (double)
     */
    [[nodiscard]] double getDistance() const;

    /**
     * @brief Get origin vertex
     * @return pointer to origin vertex
     */
    [[nodiscard]] Vertex* getOrigin() const;

    /**
     * @brief Get destination vertex
     * @return pointer to destination vertex
     */
    [[nodiscard]] Vertex* getDestination() const;

    /**
     * @brief Get reverse edge if existent, else null.
     * @return pointer to edge
     */
    [[nodiscard]] Edge* getReverseEdge() const;

    /**
     * @brief Changes the old distance of the edge
     * @param _distance - new distance for the edge
     */
    void setDistance(double _distance);

    /**
     * @brief Set new reverse edge for this edge
     * @if Edge* is not null then reverse is set
     * @else reverse edge don't changes.
     */
    void setReverseEdge(Edge* reverse);

private:
    Vertex* origin; /**< Pointer to the origin vertex >**/
    Vertex* destination; /**< Pointer to the destination vertex >**/
    double distance; /**< Distance between two vertices >**/
    Edge* reverse = nullptr;  /**< Pointer to reverse edge >**/
};

#endif //TSP_ANALYSIS_EDGE_H
