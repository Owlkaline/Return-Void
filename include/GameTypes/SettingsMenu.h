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
    void drawCursor();
    void drawBackground();
    
    int numOfButtons;    
    
    float cursorX, cursorY, cursorRadius;
    
    CheckBox checkBox;
    Button buttons[2];
    GLuint background, cursorTexture;
};

#endif
