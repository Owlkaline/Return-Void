#ifndef PAUSEDMENU_H
#define PAUSEDMENU_H

#include <string>

#include "./Label.h"
#include "./Button.h"
#include "../defines.h"
#include "../Namespaces/LoadTexture.h"

class PausedMenu {
  public:
    void draw();
    void setup();
    void drawBackground();
    void update(float mouseX, float mouseY, unsigned int* mouseBtnState);
   
    bool isPaused();
    bool hasEnded();
  protected:
    bool paused, ended;
  
    float x, y, width, height;
  
    Button Resume, Quit;
    Label lbTitle;  
    GLuint Texture;
};

#endif
