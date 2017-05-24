#include "../../include/Drops/Shield.h"

Shield::Shield() {
  this->tick = 100;
  this->width = 35;
  this->height = 45;
  this->visible = true;
  this->isCollected = false;
  this->name = "Shield";
}

void Shield::draw(GraphicsHandler *graphics) {
  if(!isCollected) {
    //drawQuad(x, -width, y, height, UP);
    graphics->drawObject(glm::vec2(x, y), glm::vec2(width, height), "PowerupShield");
  }   
}

void Shield::setup(float x, float y) {
  this->x = x;
  this->y = y;
}

void Shield::update(float deltaTime) {
  tick++;
  if(!isCollected) {
    y-=1.5 * (tick/100.0)*deltaTime;
  }
  
  if(y < 0 - height)
    visible = false;
  if(y > SPACE_Y_RESOLUTION+height)
    visible = false;
  if(x < -width) 
    visible = false;
  if(x > SPACE_X_RESOLUTION+width)
    visible = false;
} 

int Shield::getType() {
  isCollected = true;
  return SHIELD;
}
