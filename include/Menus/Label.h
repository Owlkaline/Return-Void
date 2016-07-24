#ifndef LABEL_H
#define LABEL_H

#include "../defines.h"
#include "../Namespaces/LoadTexture.h"
#include "./Text.h"


class Label {
  public:
    ~Label();
    Label();
    
    void draw();
    void clean();
    void update();
    void setup(float x, float y, float width, float height, char* filename);
    void setup(float x, float y, float scale);
    void setup(float x, float y, float scale, bool timer);
    
    //Draws Text to the screen
    void drawChar();    
    void setTimer(int time);
    void setTexture(char* filename);
    void setText(const char* str, int length);
    void setColour(float R, float G, float B);
    
    void enable() { disabled = false; }
    void disable() { disabled = true;  }    
    
    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }
    void setWidth(float width) { this->width = width; }
    void setHeight(float height) { this->height = height; }       
    void setVisible(bool visible) { this->visible = visible; }
    void setTextureVisiable(bool visible) { hasTexture = visible; }
    
    void drawBorder(bool border) { this->hasBorder = border; }
    void fill(float fR, float fG, float fB) { this->fillR = fR; this->fillG = fG; this->fillB = fB; isFilled = true; }
    
    bool timeExpired() {
      if(isTimed) {
        if(ticks <= 0)
          return true;
      }
      return false;
    }

  protected:    
    void drawBox();
    
    int length;
    int ticks;
    
    bool visible;
    bool disabled;  
    bool isFilled;
    bool hasBorder;
    bool hasTexture, isTimed;
    
    float scale;
    float R, G, B;
    float fillR, fillG, fillB;
    float x, y, width, height;
    
    char str[50];
 
    //Text text;
    GLuint Texture;
};

#endif
