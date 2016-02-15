/* 
 * File:   AquaParam.h
 * Author: fpereira
 *
 * Created on December 4, 2014, 4:34 PM
 */

#ifndef AQUAPARAM_H
#define	AQUAPARAM_H

#include <stdarg.h>
#include <string>
#include <vector>

#include "AquaParamFeature.h"

class AquaParam {
public:
    AquaParam();
    AquaParam(const AquaParam& orig);
    virtual ~AquaParam();
    
    static void startArgs(int , char**);
    
    static void addParam(AquaParamFeature *);
    static void checkRequireds();
    static std::vector<AquaParamFeature *> features;
private:
    
};

#endif	/* AQUAPARAM_H */

