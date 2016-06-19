#ifndef DROPS_H
#define DROPS_H

#include "../Namespaces/LoadTexture.h"

class Drops {
  public:
    virtual void draw() = 0;
    virtual void setup(float x, float y) = 0;
    virtual void update() = 0;
    
    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }
    float getX() { return x; }
    float getY() { return y; }
    bool isVisible() { return visible; }
  protected:
    float x, y, width, height;
    bool visible;
    
    static GLuint getCoinTexture() {
      static GLuint coinText = txt::LoadTexture("Textures/Game/Powerups/Coin.png");
      return coinText;
    }
};

#endif
