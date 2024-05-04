/**
 * @file CustomError.cpp
 * @brief Implementation of custom errors
 */

/**< Project headers >**/
#include "CustomError.h"


const char* CustomError::what() const noexcept {
    return this->message.c_str();
}
