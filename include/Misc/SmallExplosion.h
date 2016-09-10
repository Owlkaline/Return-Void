#ifndef SMALLEXPLOSIION_H
#define SMALLEXPLOSIION_H

#include "../defines.h"
#include "../Namespaces/LoadTexture.h"

class SmallExplosion {
  public:
    SmallExplosion();
    ~SmallExplosion();
    
    void draw();
    void update(float deltaTime);
    void setup(float x, float y, float dirX, float dirY);
    
    bool hasExpired();
    
  protected:
    bool expired;
  
    int size;
    float timer;
    float pos[2];
    float dirX, dirY;
    
    GLuint texture;
};

#endif
