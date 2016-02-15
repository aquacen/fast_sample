/* 
 * File:   AquaFile.cpp
 * Author: fpereira
 * 
 * Created on December 5, 2014, 11:23 AM
 */

#include "AquaFile.h"
#include "AquaException.h"

#include <string>
#include <stdio.h>
using namespace std;

AquaFile::AquaFile() {
}

AquaFile::AquaFile(const AquaFile& orig) {
}

AquaFile::~AquaFile() {
    for (int i=0; i<openneds.size(); i++){
        if (openneds[i]) fclose(openneds[i]);
    }
}

FILE* AquaFile::open(std::string path, std::string type) {
    FILE * pt = fopen(path.c_str(), type.c_str());
    if (!pt){
        AquaException e;
        e.msg = "Unable to open file: " + path;
        throw e;
    }
    openneds.push_back(pt);
    return pt;
}
