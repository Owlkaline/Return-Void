#ifndef LABEL_H
#define LABEL_H

#include "../defines.h"
#include "../Namespaces/LoadTexture.h"



class Label {
  public:
    Label();
    
    void draw();
    void clean();
    void setup(float x, float y, float scale, bool timer);
    void update();

    
    //Draws Text to the screen
    void drawChar();
    void setTexture(char* filename);
    void setAlignment(int alignment);
    void setTimer(int time);
    void setText(const char* str, int length);
    void setColour(float R, float G, float B);
    
    bool timeExpired() {
      if(isTimed) {
        if(ticks <= 0)
          return true;
      }
      return isTimed;
    }

  protected:    
    char str[25];
    float R, G, B;
    int length, align; 
    int ticks;
    float x, y, width, height;
    bool hasTexture, isTimed;
    float scale;
    GLuint Texture;
};

#endif
