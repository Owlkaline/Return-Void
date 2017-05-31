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
  this->width = 32*text.length()*scale;
  this->height = 66*scale;
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
  this->width = 32*text.length()*scale;
  this->height =  66*scale;
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
//    if(mouseY > y-height/2 && mouseY < y+height/2 && mouseX > x-width/2 && mouseX < x+width/2) {
    if(mouseY > y && mouseY < y+height/2 && mouseX > x-width/4 && mouseX < x+width/4*3) {
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
  this->width = 32*text.length()*scale;
  this->height = 66*scale;
}

void Button::setColour(glm::vec3 colour) {
  textColour = colour;
}

bool Button::Clicked() {
  return hasBeenClicked;
}

void Button::drawBox(GraphicsHandler *graphics) {
  float border = 5;
  if(height > width) {
    border = width/10;
  } else {
    border = height/10;
  }

  graphics->useShader("basic");
  graphics->drawObject(glm::vec2(x-width/2, y), glm::vec2(border, height), "Edge");
  graphics->drawObject(glm::vec2(x+width/2, y), glm::vec2(border, height), "Edge");
  graphics->drawObject(glm::vec2(x, y-height/2), glm::vec2(width*4, border/4), "Edge");
  graphics->drawObject(glm::vec2(x, y+height/2), glm::vec2(width*4, border/4), "Edge");
}

