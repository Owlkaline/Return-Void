#ifndef SHOP_H
#define SHOP_H

#include <vector>

#include "../defines.h"
#include "../Menus/Button.h"
#include "../GameTypes/Menu.h"
#include "../Menus/CheckBox.h"

class Shop: public Menu {
  public:
    Shop();
    
    void setup();
    void restart();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);

  protected:
};

#endif
