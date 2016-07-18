#ifndef FLOATINGTEXT_H
#define FLAOTINGTEXT_H

#include "./Label.h"

class FloatingText {
  public:
    ~FloatingText();
    FloatingText();
    
    void draw();
    void clean();
    void setup(float x, float y, float width, float height, char* filename);
    void setup(float x, float y, const char* str, int length, float scale);
    void update();
    
    void setTexture(char* filename);
    void setTimer(int time);
    void setText(const char* str, int length);
    void setColour(float R, float G, float B);
    
    bool getVisible() { return visible; }

  protected:    
    Label lb;
    int ticks;
    int x, y;
    bool visible;    
};

#endif
