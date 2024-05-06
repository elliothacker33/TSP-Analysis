#ifndef TSP_ANALYSIS_CUSTOMERROR_H
#define TSP_ANALYSIS_CUSTOMERROR_H

/**
 * @file CustomError.h
 */

/**< STD headers >**/
#include <iostream>
#include <exception>

using namespace std;
/**
 * @class CustomError
 * @brief This class provides a simple interface for custom errors in my program
 */
enum ERROR_TYPE{
    INFO,
    ERROR,
    SEMANTIC_ERROR
};

class CustomError : public exception {
public:
    /**
     * @constructor CustomError
     * @param _message error message
     */
    explicit CustomError(const string & _message, ERROR_TYPE _type) : message(_message), type(_type){};

    /**
     * @brief Override function of exception
     * @return message of error
     */
    [[nodiscard]] const char* what() const noexcept override;

private:
    const string& message; /**< Custom error message >**/
    ERROR_TYPE type; /**< Error type >**/

};

#endif //TSP_ANALYSIS_CUSTOMERROR_H
