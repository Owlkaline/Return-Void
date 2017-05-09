#ifndef SETTINGS_H
#define SETTINGS_H

#include <fstream>

#include "./File.h"
#include "../defines.h"
//#include <sys/types.h>
#include <sys/stat.h>

# ifdef __WIN32__
    # include <shlobj.h>
    # include <windows.h>
# endif

class Settings {
  public:
    ~Settings();
    
    static Settings *init();
    static Settings *instance();
    static void destroy();
    
    void Load();
    void Save();
    
    void setResolution(int resX, int resY) { this->windowWidth = resX; this->windowHeight = resY; }
    void setWindowWidth(int windowWidth) { this->windowWidth = windowWidth; }
    void setWindowHeight(int windowHeight) { this->windowHeight = windowHeight; }
    void setFullscreen(bool fullscreen) { this->fullscreen = fullscreen; }
    
    float getVersion() { return version; }
    
    int getWindowWidth() { return windowWidth; }   
    int getWindowHeight() { return windowHeight; } 
    int getCurrentWindowWidth() { return crntWindowWidth; }   
    int getCurrentWindowHeight() { return crntWindowHeight; } 
    
    bool getFullscreen() { return fullscreen; }
  protected:
    void createNewSettings();

    float version;
    
    bool fullscreen;
    
    int windowWidth, windowHeight, crntWindowWidth, crntWindowHeight;
    
    std::string home;
    
    std::ifstream ifs;
    std::ofstream ofs;

    static Settings *m_instance;
    
    Settings();
};

#endif

