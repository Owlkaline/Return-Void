#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <fstream>

#include "./File.h"
#include "../defines.h"

class Highscore {
  public:
    Highscore();
    ~Highscore();
    
    void Load();
    void Save();    
    
    float getVersion() { return version; }
    
    const char* getName(int index) { 
      std::string str = "";
      for(int i = 0; i < 6; ++i)
        str += name[index][i];
      return str.c_str(); 
    }
    
    int getScore(int index) { return highscores[index]; }
    
  protected:
    void createNewHighscore();
    
    float version;
    
    int highscores[10];
    char name[10][6];  
    
    std::ifstream ifs;
    std::ofstream ofs;
};

#endif

