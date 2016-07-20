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
    
    bool setNewHighscore(std::string str, int highscore) {
       for(int i = 0; i < 10; ++i) {
         if(highscore > highscores[i]) {
           for(int j = 9; j > i; j--) {
             for(int k = 0; k < 6; ++k)
               name[j][k] = name[j-1][k];
             highscores[j] = highscores[j-1];
           }
           highscores[i] = highscore;
          
           for(int j = 0; j < 6; ++j) {
             name[i][j] = str[j];
             newName[j] = str[j];
           }
           
           newHighscore = highscore;
           posNewScore = i;
           isNewHighscore = true;
           Save();
           return true;
         }
       }
       return false; 
    }
    
    const char* getName(int index) { 
      std::string str = "";
      for(int i = 0; i < 6; ++i)
        str += name[index][i];
      return str.c_str(); 
    }
    
    int getScore(int index) { return highscores[index]; }
    
    bool hasNewHighscore() { return newHighscore; }
    const char* getHighscoreName() {
      std::string str = "";
      for(int i = 0; i < 6; ++i)
        str += newName[i];
      return str.c_str(); 
    }
    int getNewHighscore() { return newHighscore; }
    int getNewHighscorePos() { return posNewScore; }
    
  protected:
    void createNewHighscore();
    
    float version;
    
    bool isNewHighscore;
    int posNewScore;
    int newHighscore;
    char newName[7];
     
    int highscores[10];
    char name[10][7];  
    
    std::ifstream ifs;
    std::ofstream ofs;
};

#endif

