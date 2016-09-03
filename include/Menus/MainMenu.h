#ifndef MAINMENU_H
#define MAINMENU_H

#include "../GameTypes/Menu.h"

class MainMenu: public Menu {
  public:
    MainMenu();
    
    void setup();
    void restart();
    void update(float mX, float mY, float deltaTime, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);

  protected:
};

#endif
