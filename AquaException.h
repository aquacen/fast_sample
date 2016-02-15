/* 
 * File:   AquaException.h
 * Author: fpereira
 *
 * Created on December 4, 2014, 4:36 PM
 */

#ifndef AQUAEXCEPTION_H
#define	AQUAEXCEPTION_H

#include <exception>
#include <string>
using namespace std;

class AquaException: public exception {
public:
    string msg;
    virtual const char* what() const throw();
    virtual ~AquaException() throw();
private:

};

#endif	/* AQUAEXCEPTION_H */

