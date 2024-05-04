#ifndef TSP_ANALYSIS_COORDINATES_H
#define TSP_ANALYSIS_COORDINATES_H

/**
 * @file Coordinates.h
 * @brief This file contains the header for a coordinates class
 */


/**
 * @class Coordinate
 * @brief Class Coordinate used to represent the coordinates of a vertex
 */
class Coordinate {
public:
    /**
     * @constructor Coordinate
     * @param latitude
     * @param longitude
     */
    Coordinate(double latitude, double longitude);

    /**
     * @brief This method returns the latitude (-90 to 90 degrees inclusive)
     * @return latitude
     */
    [[nodiscard]]  double getLatitude() const;

    /**
     * @brief This method returns the longitude (-180 to 180 degrees inclusive)
     * @return longitude
     */
    [[nodiscard]] double getLongitude() const;

    /**
     * @brief Set a new latitude
     * @param latitude
     */
    void setLatitude(double latitude);

    /**
     * @brief Set a new longitude
     * @param longitude
     */
    void setLongitude(double longitude);

private:
    double latitude; /**< Latitude field >**/
    double longitude; /**< Longitude field >**/
};


#endif //TSP_ANALYSIS_COORDINATES_H
