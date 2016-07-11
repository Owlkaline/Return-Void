#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "../GameTypes/Menu.h"

class SettingsMenu: public Menu {
  public:
    SettingsMenu();
    
    void setup();
    void restart();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);

  protected:    
    bool isRelative;
};

#endif
