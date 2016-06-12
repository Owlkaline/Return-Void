#ifndef DISPLAYMANAGER
#define DISPLAYMANAGER

#include "../defines.h"
#include "../Namespaces/LoadTexture.h"

class DisplayManager {
  public:
    //DisplayManager();
    virtual void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) = 0;
    virtual void draw() = 0;
    virtual void setup() = 0;
    virtual void restart() = 0;
    virtual void clean() = 0;
    unsigned int getSeed() { return seed; };
    void setSeed(unsigned int newSeed) { seed = newSeed; srand(seed); }
    int getEndType() { return type; }
    bool hasEnded() { return ended; }
  protected:
    unsigned int seed;
    bool ended;
    int type;
};

#endif
