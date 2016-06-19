#ifndef HIGHSCORESCREEN_H
#define HIGHSCORESCREEN_H

#include <string>
#include <sstream>

#include "./Label.h"
#include "./Button.h"
#include "../defines.h"
#include "../Namespaces/File.h"
#include "../Namespaces/LoadTexture.h"

class HighscoreScreen {
  public:
    void draw();
    void setup();
    void drawBackground();
    void update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState);
   
    void setScore(int score);
    bool hasEnded();
  protected:
    void saveDefaults();
    void LoadHighscores(int score);
    int highscores[10];
    std::string names[10];
  
    bool ended;
  
    Button Retry, Quit;
    Label lbTitle, lbScore; 
    Label lbHighscoreNames[10], lbHighscores[10]; 
};

#endif
