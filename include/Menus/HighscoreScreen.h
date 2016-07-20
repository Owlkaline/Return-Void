#ifndef HIGHSCORESCREEN_H
#define HIGHSCORESCREEN_H

#include <sstream>

#include "../GameTypes/Menu.h"

#include "../Namespaces/Highscore.h"
#include "../Namespaces/File.h"


class HighscoreScreen: public Menu {
  public:
    void setup();
    void setup(std::string username);
    void restart();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);

    void setScore(int score);
  protected:
    bool showingHighscores;
    void drawBackground() { glColor4f(0.0, 0.0,0.0,0.0f); }

    int highscores[10];
    
    Highscore highscore;
    
    std::string username;
    
    std::string names[10];
};

#endif
