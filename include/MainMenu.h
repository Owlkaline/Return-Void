#ifndef MainMenu_H
#define MainMenu_H

#include <vector>

#include "./DisplayManager.h"
#include "./defines.h"
#include "./LoadTexture.h"
#include "./Button.h"

class MainMenu: public DisplayManager {
  public:
    MainMenu();
    
    void draw();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);
    void setup();
    void restart();
    void clean();
  protected:
    float cursorX, cursorY, cursorRadius;
    void drawCursor();
    void drawBackground();
    GLuint background, cursorTexture;
    Button buttons[4];
    int numOfButtons;
    //std::vector<Button*> buttons;
   // Button buttons;
};

#endif
