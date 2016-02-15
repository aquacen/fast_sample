/* 
 * File:   AquaParam.cpp
 * Author: fpereira
 * 
 * Created on December 4, 2014, 4:34 PM
 */

#include "AquaParam.h"
#include "AquaException.h"

#include <stdarg.h>
#include <iostream>
#include <string>
using namespace std;

AquaParam::AquaParam() {
    
}
void AquaParam::startArgs(int argc, char** argv) {
    int argcc = 1;
    while (argcc < argc){
        std::string aux = std::string(argv[argcc]);
        if (aux.at(0) == '-') {
            bool found = false;
            for (int i=0; i<AquaParam::features.size(); i++){
                if (AquaParam::features[i]->key == aux){
                    if (AquaParam::features[i]->valuable){
                        if (argcc < argc-1){
                            argcc++;
                            AquaParam::features[i]->value = std::string(argv[argcc]);
                        }
                    } else {
                        AquaParam::features[i]->value = "T";
                    }
                    found = true;
                    break;
                }
            }
            if (!found){
                AquaException e;
                e.msg = "Unknow parameter: " + aux;
                throw e;
            }
        }
        argcc++;
    }
}

AquaParam::AquaParam(const AquaParam& orig) {
}

AquaParam::~AquaParam() {
}

void AquaParam::addParam(AquaParamFeature* a) {
    AquaParam::features.push_back(a);
}

void AquaParam::checkRequireds() {
    for (int i=0; i<AquaParam::features.size(); i++){
        if (AquaParam::features[i]->required && AquaParam::features[i]->value == ""){
            AquaException e;
            e.msg = "Parameter '" + AquaParam::features[i]->key + "' is required.";
            throw e;
        }
    }
}
