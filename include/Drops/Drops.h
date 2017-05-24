#ifndef DROPS_H
#define DROPS_H

#include <string>

#include "../Menus/Label.h"
#include "../GraphicsHandler.h"

class Drops {
  public:
    virtual void draw(GraphicsHandler *graphics) = 0;
    virtual void setup(float x, float y) = 0;
    virtual void update(float deltaTime) = 0;
    
    virtual int getType() = 0;
    
    
    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }
    
    bool getVisible() { return visible; }
    
    bool getCollected() { return isCollected; }
    
    float getX() { return x; }
    float getY() { return y; }
    float getWidth() { return width; }
    float getHeight() { return height; }

    std::string getName() { return name; }
  protected:
    int tick;
        
    float x, y, width, height;
    
    bool visible, isCollected;
    
    std::string name;
};

#endif
