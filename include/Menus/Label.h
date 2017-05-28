#ifndef LABEL_H
#define LABEL_H

#include "../defines.h"
#include "../GraphicsHandler.h"
#include "../Namespaces/Settings.h"

#include<string>

class Label {
  public:
    ~Label();
    Label();
    
    void draw(GraphicsHandler *graphics);
    void clean();
    void update(float deltaTime);
    void setup(float x, float y, float width, float height, std::string filename);
    void setup(float x, float y, float scale);
    void setup(float x, float y, float scale, std::string);
    void setup(float x, float y, float scale, glm::vec3 colour, std::string);
    void setup(float x, float y, float scale, bool timer);
    
    //Draws Text to the screen
    void drawChar(GraphicsHandler *graphics);    
    void setTimer(int time);
    void setTexture(std::string filename);
    void setText(std::string str);
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
    void drawBox(GraphicsHandler *graphics);
    
    float ticks;
    
    bool visible;
    bool disabled;  
    bool isFilled;
    bool hasBorder;
    bool hasTexture, isTimed;
    
    float scale;
    float fillR, fillG, fillB;
    float x, y, width, height;
    
    glm::vec3 colour;
    std::string str;

    std::string texture;
};

#endif
