#ifndef LABEL_H
#define LABEL_H

#include "../defines.h"
#include "../GraphicsHandler.h"
#include "../Namespaces/Settings.h"
//#include "./Text.h"
#include "GL/glc.h"

#include<string>

class Label {
  public:
    ~Label();
    Label();
    
    void draw();
    void clean();
    void update(float deltaTime);
    void setup(float x, float y, float width, float height, char* filename);
    void setup(float x, float y, float scaleX, float scaleY);
    void setup(float x, float y, float scaleX, float scaleY, bool timer);
    
    void setupGLC(float scaleX, float scaleY);
    
    //Draws Text to the screen
    void drawChar();    
    void setTimer(int time);
    void setTexture(char* filename);
    void setText(std::string str, int length);
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
    float ticks;
    
    bool visible;
    bool disabled;  
    bool isFilled;
    bool hasBorder;
    bool hasTexture, isTimed;
    
    float scaleX, scaleY;
    float R, G, B;
    float fillR, fillG, fillB;
    float x, y, width, height;
    
    std::string str;
       
    GLint ctx, myFont;
 
    //Text text;
    GLuint Texture;
};

#endif
