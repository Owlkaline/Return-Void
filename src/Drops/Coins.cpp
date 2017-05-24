#include "../../include/Drops/Coins.h"

Coins::Coins() {
  this->tick = 100;
  this->width = 50;
  this->height = 50;
  this->visible = true;
  this->isCollected = false;
  this->name = "10 Coins";
}

void Coins::draw(GraphicsHandler *graphics) {
  if(!this->isCollected) {
    //drawQuad(x, -width, y, height, UP);
    graphics->drawObject(glm::vec2(x, y), glm::vec2(width, height), "PowerupCoin");
  }
}

void Coins::setup(float x, float y) {
  this->x = x;
  this->y = y;
}

void Coins::update(float deltaTime) {
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

int Coins::getType() {
  this->isCollected = true;
  return COIN;
}
