#ifndef LABEL_H
#define LABEL_H

#include "../defines.h"
#include "../Namespaces/LoadTexture.h"



class Label {
  public:
    ~Label();
    Label();
    
    void draw();
    void clean();
    void setup(float x, float y, float width, float height, char* filename);
    void setup(float x, float y, float scale);
    void setup(float x, float y, float scale, bool timer);
    void update();

    
    //Draws Text to the screen
    void drawChar();
    void setTexture(char* filename);
    void setTimer(int time);
    void setText(const char* str, int length);
    void setColour(float R, float G, float B);
    
    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }
    void setWidth(float width) { this->width = width; }
    void setHeight(float height) { this->height = height; }
    
    void fill(float fR, float fG, float fB) { this->fillR = fR; this->fillG = fG; this->fillB = fB; isFilled = true; }
    
    bool timeExpired() {
      if(isTimed) {
        if(ticks <= 0)
          return true;
      }
      return false;
    }
    
    void drawBorder(bool border) { this->hasBorder = border; }
    void setTextureVisiable(bool visible) { hasTexture = visible; }

  protected:    
    void drawBox();
    
    bool isFilled;
    bool hasBorder;
    char str[50];
    float R, G, B;
    float fillR, fillG, fillB;
    int length;
    int ticks;
    float x, y, width, height;
    bool hasTexture, isTimed;
    float scale;
    GLuint Texture;
};

#endif
