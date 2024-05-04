/**
 * @file Coordinates.cpp
 * @brief This file contains the implementation of coordinates
 */

#include "Coordinates.h"
#include "../Exceptions/CustomError.h"

 Coordinate::Coordinate(double latitude, double longitude){

    if (latitude >= -90.0 && latitude <= 90.0){
        this->latitude = latitude;
    }
    else {
        throw CustomError("Semantic error: Latitude must be between values -90 and 90 (inclusive)");
    }

    if (longitude >= -180.0 && longitude <= 180.0){
        this->longitude = longitude;
    }
    else{
        throw CustomError("Semantic error: Longitude must be between values -180 and 180 (inclusive)");
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
        throw CustomError("Semantic error: Latitude must be between values -90 and 90 (inclusive)");
    }
}

void Coordinate::setLongitude(double _longitude) {
    if (longitude >= -180.0 && longitude <= 180.0){
        this->longitude = _longitude;
    }
    else{
        throw CustomError("Semantic error: Longitude must be between values -180 and 180 (inclusive)");
    }
}


