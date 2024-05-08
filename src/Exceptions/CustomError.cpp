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
    else if (this->type == FILE_ERROR){
        return ("FILE ERROR: " + this->message).c_str();
    }
    else if (this->type == PARSE_ERROR){
        return ("PARSE ERROR: " + this->message).c_str();
    }
    else if (this->type == MENU_ERROR){
        return ("MENU ERROR: " + this->message).c_str();
    }
    return ("ERROR: " + this->message).c_str();

}
