/* 
 * File:   AquaFile.h
 * Author: fpereira
 *
 * Created on December 5, 2014, 11:23 AM
 */

#ifndef AQUAFILE_H
#define	AQUAFILE_H

#include <string>
#include <vector>

class AquaFile {
public:
    AquaFile();
    AquaFile(const AquaFile& orig);
    virtual ~AquaFile();
    
    FILE * open(std::string, std::string);
    
    std::vector<FILE *> openneds;
private:

};

#endif	/* AQUAFILE_H */

