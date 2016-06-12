#ifndef BUTTON_H
#define BUTTON_H

#include "../defines.h"
#include "../Namespaces/LoadTexture.h"



class Button {
   
  public:
    Button();
    void setup(float x, float y, float width, float height);

    void draw();
    void update(float mouseX, float mouseY, unsigned int* mouseBtnState);
    void clean();
    //Draws Text to the screen
    void drawChar();
    void setTexture(char* filename);
    void setAlignment(int alignment);
    void setText(char str[25], int length);
    void setColour(float R, float G, float B);

    bool checkIfClicked();
    //static void bindTexture();
  protected:
    bool isSelected, hasTexture, hasBeenClicked;
    float x, y, width, height;
    float R, G, B;
    char str[25];
    int length, align;
    //static GLuint Texture;
    //static GLuint getTexture();
    GLuint Texture;
};
//GLuint Button::Texture = txt::LoadTexture("Textures/Menu/Button.png");
//GLuint Button::Texture = txt::LoadTexture("Textures/Menu/Button.png");

#endif
