/* 
 * File:   AquaParamFeature.cpp
 * Author: fpereira
 * 
 * Created on December 4, 2014, 5:18 PM
 */

#include "AquaParamFeature.h"
#include "AquaParam.h"

AquaParamFeature::AquaParamFeature(std::string a, bool v, std::string h) {
    this->key = a;
    this->valuable = v;
    this->required = (h.substr(0, 1)=="*")?true:false;
    this->help = h;
    
    this->value = "";
    AquaParam::addParam(this);
}

AquaParamFeature::AquaParamFeature(const AquaParamFeature& orig) {
}

AquaParamFeature::~AquaParamFeature() {
}

