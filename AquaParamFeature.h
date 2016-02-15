/* 
 * File:   AquaParamFeature.h
 * Author: fpereira
 *
 * Created on December 4, 2014, 5:18 PM
 */

#ifndef AQUAPARAMFEATURE_H
#define	AQUAPARAMFEATURE_H

#include <string>

class AquaParamFeature {
public:
    AquaParamFeature(std::string, bool, std::string);
    AquaParamFeature(const AquaParamFeature& orig);
    virtual ~AquaParamFeature();
    
    std::string key;
    std::string value;
    
    bool required;
    bool valuable;
    std::string help;
private:

};

#endif	/* AQUAPARAMFEATURE_H */

