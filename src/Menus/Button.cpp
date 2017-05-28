#include "../../include/Menus/Button.h"

Button::Button() {

}

Button::~Button() {
  texture = "";
  text = "";
}

void Button::draw(GraphicsHandler *graphics) {  
  if(visible) {
    if(isFilled) {
     /* glColor3f(fillR, fillG, fillB);
      drawQuad(x, -width, y, height, UP);*/
    }
    glm::vec3 colour = textColour;
    if(disabled) {
      //colour = textColour*glm::vec3(0.5f);
    } else if(clicked || hasBeenClicked) {
      colour = glm::vec3(0.0f, 0.0f, 0.0f);
    } else if(isSelected) {
      colour = textColour*glm::vec3(0.5f);
    }
    if(hasTexture) {
    
     graphics->drawObject(glm::vec2(x,y), glm::vec2(width, height), texture);
     graphics->drawText(text, glm::vec2(x, y), scale, colour, "DarkCrystal");
    } else { 
     graphics->drawText(text, glm::vec2(x, y), scale, colour, "DarkCrystal");
    }
    if(hasBorder)
      drawBox(graphics);
  }
}

void Button::clean() {

}

void Button::setup(float x, float y, float scale, std::string text) {
  isSelected = false;
  hasTexture = false;
  clicked = false;
  hasBeenClicked = false;
  hasBorder = false;
  isFilled = false;
  disabled = false;
  visible = true;
  
  textColour = glm::vec3(1.0f);
  
  this->text = text;
  
  this->x = x;
  this->y = y;
  this->scale = scale;
  this->width = -1;
  this->height = -1;
}

void Button::setup(float x, float y, float width, float height, std::string texture) {
  isSelected = false;
  hasTexture = true;
  clicked = false;
  hasBeenClicked = false;
  hasBorder = false;
  isFilled = false;
  disabled = false;
  visible = true;
  
  textColour = glm::vec3(1.0f);
  this->texture = texture;
  
  this->x = x;
  this->y = y;
  this->width = width;
  this->width = width;
  this->scale = scale;
}

void Button::setup(float x, float y, float scale, glm::vec3 colour, std::string text) {
  isSelected = false;
  hasTexture = false;
  clicked = false;
  hasBeenClicked = false;
  hasBorder = false;
  isFilled = false;
  disabled = false;
  visible = true;
  
  textColour = colour;
  this->text = text;
  
  this->x = x;
  this->y = y;
  this->scale = scale;
  this->width = -1;
  this->height = -1;
}

void Button::setup(float x, float y, float width, float height, float scale, glm::vec3 colour, std::string text, std::string texture) {
  isSelected = false;
  hasTexture = true;
  clicked = false;
  hasBeenClicked = false;
  hasBorder = false;
  isFilled = false;
  disabled = false;
  visible = true;
  
  textColour = colour;
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->scale = scale;
}

void Button::setup(float x, float y, float width, float height, float scale, std::string text, std::string texture) {
  isSelected = false;
  hasTexture = true;
  clicked = false;
  hasBeenClicked = false;
  hasBorder = false;
  isFilled = false;
  disabled = false;
  visible = true;
  
  textColour = glm::vec3(1.0f);
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->scale = scale;
}

void Button::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState) {
  hasBeenClicked = false;
  isSelected = false;
  if(!disabled) {
    if(mouseBtnState[0] == 0)
      clicked = false;
    if(mouseY > y-height/2 && mouseY < y+height/2 && mouseX > x-width/2 && mouseX < x+width/2) {
      if(mouseBtnState[0] == 1) {
        clicked = true;
      } 
      if(mouseBtnState[0] == 0 && prevMouseBtnState[0] == 1) {
        hasBeenClicked = true;
      }
      isSelected = true;
    } else {
      isSelected = false;
      clicked = false;
      hasBeenClicked = false;
    }
  }
}
/*
void Button::setTexture(char* filename) {
  Texture = filename;
  hasTexture = true;
}
*/
void Button::setText(std::string str) {
  text = str;
}

void Button::setColour(glm::vec3 colour) {
  textColour = colour;
}

bool Button::Clicked() {
  return hasBeenClicked;
}

void Button::drawBox(GraphicsHandler *graphics) {
  float border = 5;
 /* glColor3f(0.0, 0.0, 0.0);
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
  glColor3f(1.0, 1.0, 1.0);*/
  
  graphics->drawObject(glm::vec2(x+border/2, y), glm::vec2(width, height), "Edge");
  graphics->drawObject(glm::vec2(x-border/2, y), glm::vec2(width, height), "Edge");
  graphics->drawObject(glm::vec2(x, y-border/2), glm::vec2(width, height), "Edge");
  graphics->drawObject(glm::vec2(x, y+border/2), glm::vec2(width, height), "Edge");
}

