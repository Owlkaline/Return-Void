#ifndef DISPLAYMANAGER
#define DISPLAYMANAGER

#include "./defines.h"

class DisplayManager {
  public:
    //DisplayManager();
    virtual void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) = 0;
    virtual void draw() = 0;
    virtual void setup() = 0;
    virtual void restart() = 0;
    virtual void clean() = 0;
    int getEndType() { return type; }
    bool hasEnded() { return ended; }
  protected:
    bool ended = false;
    int type;
};

#endif
