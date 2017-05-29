#ifndef FLOATINGTEXT_H
#define FLAOTINGTEXT_H

#include "./Label.h"
#include "../GraphicsHandler.h"

class FloatingText {
  public:
    ~FloatingText();
    FloatingText();
    
    void draw(GraphicsHandler *graphics);
    void clean();
    void update(float deltaTime);
    void setup(float x, float y, float width, float height, std::string filename);
    void setup(float x, float y, float scale, std::string str);    
    
    void setTimer(int time);
    void setTexture(std::string filename);
    void setText(std::string str);
    void setColour(float R, float G, float B);
    
    bool getVisible() { return visible; }

  protected:    
    int ticks;
    int x, y;
    
    bool visible;   
    
    Label lb; 
};

#endif
