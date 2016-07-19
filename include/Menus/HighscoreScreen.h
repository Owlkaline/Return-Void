#ifndef HIGHSCORESCREEN_H
#define HIGHSCORESCREEN_H

#include <sstream>

#include "../GameTypes/Menu.h"

#include "../Namespaces/File.h"


class HighscoreScreen: public Menu {
  public:
    void setup();
    void restart();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);

    void setScore(int score);
  protected:
    void saveDefaults();
    void LoadHighscores(int score);
    void drawBackground() { glColor4f(0.0, 0.0,0.0,0.0f); }

    int highscores[10];
    
    std::string names[10];
};

#endif
