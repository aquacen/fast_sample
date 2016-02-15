/* 
 * File:   AquaUtils.h
 * Author: fpereira
 *
 * Created on December 5, 2014, 11:46 AM
 */

#ifndef AQUAUTILS_H
#define	AQUAUTILS_H

#include <string>
#include <vector>

class AquaUtils {
public:
    AquaUtils();
    AquaUtils(const AquaUtils& orig);
    virtual ~AquaUtils();
    
    static std::string getDate();
    static void mkDir(std::string);
    
    static std::vector<std::string> explode(std::string, std::string);
private:

};

#endif	/* AQUAUTILS_H */

