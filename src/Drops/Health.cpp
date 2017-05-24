#include "../../include/Drops/Health.h"

Health::Health() {
  this->tick = 100;
  this->width = 50;
  this->height = 50;
  this->visible = true;
  this->isCollected = false;
  this->name = "Health";
}

void Health::draw(GraphicsHandler *graphics) {
  if(!isCollected) {
    // drawQuad(x, -width, y, height, UP);
    graphics->drawObject(glm::vec2(x, y), glm::vec2(width, height), "PowerupHealth");
  }
}

void Health::setup(float x, float y) {
  this->x = x;
  this->y = y;
}

void Health::update(float deltaTime) {
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

int Health::getType() {
  this->isCollected = true;
  return HEALTH;
}
