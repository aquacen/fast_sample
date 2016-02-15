/* 
 * File:   AquaException.cpp
 * Author: fpereira
 * 
 * Created on December 4, 2014, 4:36 PM
 */

#include "AquaException.h"

#include <string>

const char* AquaException::what() const throw(){
    std::string msgn = this->msg + ".";
    return msgn.c_str();
}

AquaException::~AquaException() throw(){
    
}