#ifndef TSP_ANALYSIS_CUSTOMERROR_H
#define TSP_ANALYSIS_CUSTOMERROR_H

/**
 * @file CustomError.h
 */

// STD library
#include <iostream>
#include <exception>

using namespace std;
/**
 * @class CustomError
 * @brief This class provides a simple interface for custom errors in my program
 */

class CustomError : public exception {
public:
    /**
     * @constructor CustomError
     * @param _message error message
     */
    explicit CustomError(const string & _message) : message(_message) {};

    /**
     * @brief Override function of exception
     * @return message of error
     */
    [[nodiscard]] const char* what() const noexcept override;
private:
    const string& message; /**< custom error message **/
};

#endif //TSP_ANALYSIS_CUSTOMERROR_H
