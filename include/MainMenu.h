#ifndef MainMenu_H
#define MainMenu_H

#include "./DisplayManager.h"
#include "./defines.h"
#include "./LoadTexture.h"

class MainMenu: public DisplayManager {
  public:
    MainMenu();
    
    void draw();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);
    void setup();
    void restart();
    void clean();
  protected:
    void drawBackground();
    GLuint background;
};

#endif
