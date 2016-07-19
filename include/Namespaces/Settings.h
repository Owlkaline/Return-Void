#ifndef SETTINGS_H
#define SETTINGS_H

#include <fstream>

#include "./File.h"
#include "../defines.h"

class Settings {
  public:
    Settings();
    ~Settings();
    void Load();
    void Save();
    void setRelativeMovement(bool relativeMovement) { this->relativeMovement = relativeMovement; }
    
    float getVersion() { return version; }
    
    bool getRelativeMovement() { return relativeMovement; }    
  protected:
    void createNewSettings();

    float version;
    
    bool relativeMovement;
    
    std::ifstream ifs;
    std::ofstream ofs;
};

#endif

