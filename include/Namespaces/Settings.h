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
    float getVersion() { return version; }
    bool getRelativeMovement() { return relativeMovement; }
    void setRelativeMovement(bool relativeMovement) { this->relativeMovement = relativeMovement; }
  protected:
    void createNewSettings();
    std::ifstream ifs;
    std::ofstream ofs;
    float version;
    bool relativeMovement;
};

#endif

