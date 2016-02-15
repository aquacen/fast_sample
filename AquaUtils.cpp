/* 
 * File:   AquaUtils.cpp
 * Author: fpereira
 * 
 * Created on December 5, 2014, 11:46 AM
 */

#include "AquaUtils.h"
#include "AquaException.h"
#include <string>
#include <vector>
#include <sstream>
#include <time.h>
using namespace std;

#include <sys/stat.h>
struct stat sb;

AquaUtils::AquaUtils() {
}

AquaUtils::AquaUtils(const AquaUtils& orig) {
}

AquaUtils::~AquaUtils() {
}

std::string AquaUtils::getDate() {
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    
    stringstream str;
    str.str("");
    
    str << 1900 + timeinfo->tm_year;
    if (timeinfo->tm_mon<10) str << "0";
    str << timeinfo->tm_mon;
    if (timeinfo->tm_mday<10) str << "0";
    str << timeinfo->tm_mday;
    str << "_";
    if (timeinfo->tm_hour<10) str << "0";
    str << timeinfo->tm_hour;
    if (timeinfo->tm_min<10) str << "0";
    str << timeinfo->tm_min;
    if (timeinfo->tm_sec<10) str << "0";
    str << timeinfo->tm_sec;
    
    return string(str.str());
}

std::vector<string> AquaUtils::explode(std::string pat, std::string line) {
    vector<string> af;
    while(line.find(pat)!=-1){
        af.push_back(line.substr(0, line.find(pat)));
        line = line.substr(line.find(pat)+pat.size());
    }
    af.push_back(line);
    return af;
}

void AquaUtils::mkDir(std::string path) {
    stringstream cmd;
    cmd.str("");
    if (stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)){
        AquaException e;
        e.msg = "Output directory not is empty.";
        throw e;
    } else {
        cmd << "mkdir " << path;
        system(cmd.str().c_str());
    }
}


