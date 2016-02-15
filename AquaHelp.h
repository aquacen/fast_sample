/* 
 * File:   AquaHelp.h
 * Author: fpereira
 *
 * Created on December 4, 2014, 4:33 PM
 */

#ifndef AQUAHELP_H
#define	AQUAHELP_H
#include <string>

class AquaHelp {
public:
    AquaHelp();
    AquaHelp(const AquaHelp& orig);
    virtual ~AquaHelp();
    
    static void show(char **);
    static void showVersion(char **);
    static std::string name;
    static std::string version;
    
private:

};

#endif	/* AQUAHELP_H */

