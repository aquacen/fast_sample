/* 
 * File:   AquaHelp.cpp
 * Author: fpereira
 * 
 * Created on December 4, 2014, 4:33 PM
 */

#include "AquaHelp.h"
#include "AquaParam.h"
#include "AquaException.h"

#include <iostream>
#include <iostream>

using namespace std;

AquaHelp::AquaHelp() {
}

AquaHelp::AquaHelp(const AquaHelp& orig) {
}

AquaHelp::~AquaHelp() {
}

void AquaHelp::show(char ** argv) {
    cout << AquaHelp::name << " v" << AquaHelp::version << endl;
    cout << "AQUACEN (c) 2016." << endl;
    cout << endl << "Use " << string(argv[0]) << " [options]" << endl;
    cout << "        options: " << endl;
    for (int i=0; i<AquaParam::features.size(); i++){
        if (AquaParam::features[i]->help.substr(0,1)!="-"){
            cout << "             " << AquaParam::features[i]->key << "             " << AquaParam::features[i]->help.substr(1);
            if (AquaParam::features[i]->required){
                cout << " (must required)";
            }
            cout << endl;
        }
    }
    cout << endl;
    
    AquaException e;
    e.msg = "clean";
    throw e;
}

void AquaHelp::showVersion(char ** argv) {
    cout << AquaHelp::name << " v" << AquaHelp::version << endl;
    cout << "AQUACEN (c) 2015." << endl;
    cout << "Use " << string(argv[0]) << " -h to see options." << endl;
    
    AquaException e;
    e.msg = "clean";
    throw e;
}