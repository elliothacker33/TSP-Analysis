/**
 * @file CustomError.cpp
 * @brief Implementation of custom errors
 */

/**< Project headers >**/
#include "CustomError.h"

const char * CustomError::what() const noexcept {
    if (this->type == ERROR) {
        std::string error = "ERROR: ";
        error += this->message;
        cerr << error << endl;
        return nullptr;
    }
    else if (this->type == INFO){
        std::string error = "INFO: ";
        error += this->message;
        cerr << error << endl;
        return nullptr;
    }
    else if (this->type == SEMANTIC_ERROR){
        std::string error = "SEMANTIC_ERROR: ";
        error += this->message;
        cerr << error << endl;
        return nullptr;
    }
    else if (this->type == FILE_ERROR){
        std::string error = "FILE_ERROR: ";
        error += this->message;
        cerr << error << endl;
        return nullptr;
    }
    else if (this->type == PARSE_ERROR){
        std::string error = "PARSE_ERROR: ";
        error += this->message;
        cerr << error << endl;
        return nullptr;
    }
    else if (this->type == MENU_ERROR){
        std::string error = "MENU_ERROR: ";
        error += this->message;
        cerr << error << endl;
        return nullptr;
    }
    return nullptr;
}
