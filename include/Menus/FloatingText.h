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
    void setup(float x, float y, float width, float height, char* filename);
    void setup(float x, float y, const char* str, float scale);    
    
    void setTimer(int time);
    void setTexture(char* filename);
    void setText(const char* str);
    void setColour(float R, float G, float B);
    
    bool getVisible() { return visible; }

  protected:    
    int ticks;
    int x, y;
    
    bool visible;   
    
    Label lb; 
};

#endif
