#ifndef SHOP_H
#define SHOP_H

#include <vector>

#include "../defines.h"
#include "../Menus/Button.h"
#include "./DisplayManager.h"
#include "../Menus/CheckBox.h"

class Shop: public DisplayManager {
  public:
    Shop();
    
    void draw();
    void clean();
    void setup();
    void restart();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);

  protected:
    void drawBackground();
    
    int numOfButtons;    
    
    Button buttons[5];
};

#endif
