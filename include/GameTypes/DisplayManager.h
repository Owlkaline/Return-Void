#ifndef DISPLAYMANAGER
#define DISPLAYMANAGER

#include "../defines.h"

#include "../Namespaces/LoadTexture.h"

class DisplayManager {
  public:    
    virtual void draw() = 0;
    virtual void setup() = 0;    
    virtual void clean() = 0;
    virtual void restart() = 0;
    virtual void update(float mX, float mY, float deltaTime, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) = 0;
    
    void setSeed(unsigned int newSeed) { printf("New Seed:%d\n", seed); seed = newSeed; srand(seed); }
    
    bool hasEnded() { return ended; }
    
    int getEndType() { return type; }
    unsigned int getSeed() { return seed; };
  protected:
    int type;
    
    bool ended;   
     
    unsigned int seed;
};

#endif
