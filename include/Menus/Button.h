#ifndef BUTTON_H
#define BUTTON_H

#include "../defines.h"

#include "./Label.h"
#include "./Text.h"

#include "../Namespaces/LoadTexture.h"

class Button {
  public:
    ~Button();
    Button();
    
    void draw();
    void clean();
    void setup(float x, float y, float width, float height, float scale);
    void setup(float x, float y, float width, float height, char* filename);
    void update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState);

    //Draws Text to the screen
    void setTexture(char* filename);
    void setText(const char* str, int length);
    void setColour(float R, float G, float B);
    
    void setX(float x) { this->x = x; }
    void setVisible(bool visible) { this->visible = visible; }
     
    void enable() { disabled = false; }
    void disable() { disabled = true;  }    
    void drawBorder(bool border) { this->hasBorder = border; }
    void fill(float fR, float fG, float fB) { this->fillR = fR; this->fillG = fG; this->fillB = fB; isFilled = true; }
    
    float getX() { return x; }
    float getY() { return y; }
    float getWidth() { return width; }
    float getHeight() { return height; }

    bool Clicked();
    

  protected:  
    void drawBox();
    
    int length;
    
    bool visible;
    bool disabled;    
    bool isFilled;    
    bool hasBorder;
    bool isSelected, hasTexture, hasBeenClicked, clicked;
    
    float scale; 
    float R, G, B;
    float fillR, fillG, fillB;
    float x, y, width, height;
    
    char str[25];

    Label lbTitle;
    GLuint Texture;
};

#endif
