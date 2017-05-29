#ifndef PAUSEDMENU_H
#define PAUSEDMENU_H

#include "../GameTypes/Menu.h"

class PausedMenu: public Menu {
  public:
    void setup();
    void restart();
    void drawBackground(GraphicsHandler *graphics);
    void update(float mX, float mY, float deltaTime, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);
   
    bool isPaused();
  protected:
    bool paused;
  
    float x, y, width, height;
   
    std::string texture;
};

#endif
