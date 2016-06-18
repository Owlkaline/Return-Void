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
    void LoadHighscores(int score);
  
    bool ended;
  
    Button Retry, Quit;
    Label lbTitle, lbScore;  
};

#endif
