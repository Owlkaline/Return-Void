#ifndef BUTTON_H
#define BUTTON_H

#include "../defines.h"
#include "../Namespaces/LoadTexture.h"



class Button {
  public:
    Button();
    
    void draw();
    void clean();
    void setup(float x, float y, float width, float height);
    void update(float mouseX, float mouseY, unsigned int* mouseBtnState);

    //Draws Text to the screen
    void drawChar();
    void setTexture(char* filename);
    void setAlignment(int alignment);
    void setText(char str[25], int length);
    void setColour(float R, float G, float B);

    bool checkIfClicked();

  protected:    
    char str[25];
    float R, G, B;
    int length, align; 
    float x, y, width, height;
    bool isSelected, hasTexture, hasBeenClicked;
    
    GLuint Texture;
};

#endif
