/**
 * @file CustomError.cpp
 * @brief Implementation of custom errors
 */

/**< Project headers >**/
#include "CustomError.h"

const char* CustomError::what() const noexcept {
    if (this->type == ERROR){
        return ("ERROR: " + this->message).c_str();
    }
    else if (this->type == INFO){
        return ("INFO: " + this->message).c_str();
    }
    else if (this->type == SEMANTIC_ERROR){
        return ("SEMANTIC ERROR: " + this->message).c_str();
    }
    return ("ERROR: " + this->message).c_str();

}
