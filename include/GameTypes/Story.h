#ifndef STORY_H
#define STORY_H

#include "./DisplayManager.h"

#include "../Story/StarMap.h"

class Story: public DisplayManager {
  public:
    void draw(GraphicsHandler *graphics);
    void setup();    
    void clean() { }
    void restart();
    void update(float mX, float mY, float deltaTime, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);
  protected:
    StarMap world;
};

#endif
