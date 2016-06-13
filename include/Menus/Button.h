#ifndef BUTTON_H
#define BUTTON_H

#include "../defines.h"

#include "./Label.h"
#include "../Namespaces/LoadTexture.h"



class Button {
  public:
    Button();
    
    void draw();
    void clean();
    void setup(float x, float y, float width, float height, float scale);
    void update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState);

    //Draws Text to the screen
    void setTexture(char* filename);
    void setText(const char* str, int length);
    void setColour(float R, float G, float B);
    
    void setCustomHitBox(float x1, float y1, float x2, float y2);

    bool Clicked();

  protected: 
    float scale;   
    char str[25];
    float R, G, B;
    int length; 
    bool usingCustomHitBox;
    float customHitBox[4];
    float x, y, width, height;
    bool isSelected, hasTexture, hasBeenClicked;
    
    Label lbTitle;
    GLuint Texture;
};

#endif
