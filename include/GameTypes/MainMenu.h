#ifndef MainMenu_H
#define MainMenu_H

#include <vector>

#include "../defines.h"
#include "../Menus/Button.h"
#include "./DisplayManager.h"

class MainMenu: public DisplayManager {
  public:
    MainMenu();
    
    void draw();
    void clean();
    void setup();
    void restart();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);

  protected:
    void drawCursor();
    void drawBackground();
    
    int numOfButtons;    
    
    float cursorX, cursorY, cursorRadius;
    
    Button buttons[4];
    GLuint background, cursorTexture;
};

#endif
