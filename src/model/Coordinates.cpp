/**
 * @file Coordinates.cpp
 * @brief This file contains the implementation of coordinates
 */

/**< Project headers >**/
#include "Coordinates.h"
#include "../Exceptions/CustomError.h"

 Coordinate::Coordinate(double latitude, double longitude){

    if (latitude >= -90.0 && latitude <= 90.0){
        this->latitude = latitude;
    }
    else {
        throw CustomError("Latitude must be between values -90 and 90 (inclusive)", ERROR);
    }

    if (longitude >= -180.0 && longitude <= 180.0){
        this->longitude = longitude;
    }
    else{
        throw CustomError("Longitude must be between values -180 and 180 (inclusive)", ERROR);
    }
}

double Coordinate::getLatitude() const {
    return latitude;
}

double Coordinate::getLongitude() const {
    return longitude;
}

void Coordinate::setLatitude(double _latitude) {
    if (latitude >= -90.0 && latitude <= 90.0){
        this->latitude = _latitude;
    }
    else{
        throw CustomError("Latitude must be between values -90 and 90 (inclusive)", ERROR);
    }
}

void Coordinate::setLongitude(double _longitude) {
    if (longitude >= -180.0 && longitude <= 180.0){
        this->longitude = _longitude;
    }
    else{
        throw CustomError("Longitude must be between values -180 and 180 (inclusive)", ERROR);
    }
}


