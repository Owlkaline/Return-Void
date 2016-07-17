#include "../../include/Menus/Button.h"

Button::Button() {

}

Button::~Button() {
  Texture = 0;
}

void Button::draw() {
  if(hasTexture) {
    if(clicked || hasBeenClicked) {
      glColor3f(0.0f, 0.0f, 0.0f);
    } else if(isSelected) {
      glColor3f(0.5f, 0.5f, 0.5f);
    } else {
      glColor3f(1.0, 1.0, 1.0);
    }
  
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Texture);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(x-width/2, y+height/2, 0.0);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(x+width/2, y+height/2, 0.0);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(x+width/2, y-height/2, 0.0);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(x-width/2, y-height/2, 0.0);
    glEnd();  
  
    glDisable(GL_TEXTURE_2D);    
    
    if(hasBorder)
      drawBox();
  } else { 
    lbTitle.draw();
  }
  glColor3f(1.0, 1.0, 1.0);
}

void Button::clean() {

}

void Button::setup(float x, float y, float width, float height, char* filename) {
  isSelected = false;
  hasTexture = true;
  clicked = false;
  hasBeenClicked = false;
  hasBorder = false;
  
  Texture = txt::LoadTexture(filename);
  
  this->x = x;
  this->y = y;
  this->scale = 0;
  this->width = width;
  this->height = height;
}

void Button::setup(float x, float y, float width, float height, float scale) {
  isSelected = false;
  hasTexture = false;
  clicked = false;
  hasBeenClicked = false;
  hasBorder = false;
  
  this->x = x;
  this->y = y;
  this->scale = scale;
  this->width = width;
  this->height = height;
  lbTitle.setup(x, y, scale);
}

void Button::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState) {
  hasBeenClicked = false;
  isSelected = false;
  if(mouseBtnState[GLUT_LEFT_BUTTON] == BUTTON_UP)
    clicked = false;
 
  if(mouseY > y-height/2 && mouseY < y+height/2 && mouseX > x-width/2 && mouseX < x+width/2) {
    if(mouseBtnState[GLUT_LEFT_BUTTON] == BUTTON_DOWN) {
      clicked = true;
    } 
    if(mouseBtnState[GLUT_LEFT_BUTTON] == BUTTON_UP && prevMouseBtnState[GLUT_LEFT_BUTTON] == BUTTON_DOWN) {
      hasBeenClicked = true;
    }
    isSelected = true;
  } else {
    isSelected = false;
    clicked = false;
    hasBeenClicked = false;
  }
}

void Button::setTexture(char* filename) {
  Texture = txt::LoadTexture(filename);
  hasTexture = true;
}

void Button::setText(const char* str, int length) {
  lbTitle.setText(str, length);
}

void Button::setColour(float R, float G, float B) {
  lbTitle.setColour(R, G, B);
}

bool Button::Clicked() {
  return hasBeenClicked;
}

void Button::drawBox() {
  float border = 5;
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);

    // Left
    glVertex3f(x-width/2, y+height/2, 0.0);
    glVertex3f(x-width/2+border, y+height/2, 0.0);
    glVertex3f(x-width/2+border, y-height/2, 0.0);
    glVertex3f(x-width/2, y-height/2, 0.0);

    // Right
    glVertex3f(x+width/2, y+height/2, 0.0);
    glVertex3f(x+width/2-border, y+height/2, 0.0);
    glVertex3f(x+width/2-border, y-height/2, 0.0);
    glVertex3f(x+width/2, y-height/2, 0.0);

    // top
    glVertex3f(x+width/2, y+height/2, 0.0);
    glVertex3f(x+width/2, y+height/2-border, 0.0);
    glVertex3f(x-width/2, y+height/2-border, 0.0);
    glVertex3f(x-width/2, y+height/2, 0.0);

    // bottom
    glVertex3f(x+width/2, y-height/2, 0.0);
    glVertex3f(x+width/2, y-height/2+border, 0.0);
    glVertex3f(x-width/2, y-height/2+border, 0.0);
    glVertex3f(x-width/2, y-height/2, 0.0);

  glEnd();
  glColor3f(1.0, 1.0, 1.0);
}

