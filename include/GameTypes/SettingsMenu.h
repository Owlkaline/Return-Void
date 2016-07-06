#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include <vector>

#include "../defines.h"
#include "../Menus/Button.h"
#include "./DisplayManager.h"
#include "../Menus/CheckBox.h"

class SettingsMenu: public DisplayManager {
  public:
    SettingsMenu();
    
    void draw();
    void clean();
    void setup();
    void restart();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);

  protected:
    void drawBackground();
    bool isRelative;
    int numOfButtons;    
    Button buttons[3];
    Label lbTrueFalse, lbIsRelative;

    GLuint background;
};

#endif
