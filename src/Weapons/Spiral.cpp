#include "../../include/Weapons/Spiral.h"

Spiral::Spiral() {
  this->immortal = false;
  this->active = true;
}

void Spiral::draw(GraphicsHandler *graphics) {
  graphics->drawObject(glm::vec2(x, y), glm::vec2(width, height), angle, "Spiral");
}

void Spiral::reset() {

}

void Spiral::clean() {

}

void Spiral::tick(float deltaTime) {
  y+=(speed*deltaTime)*directionY;
  x+=(speed*deltaTime)*directionX;
  angle+=10*deltaTime;
}

void Spiral::setup(float x, float y, float dirX, float dirY, float angle) {
  this->x = x;
  this->y = y;
  width = 12;
  height = 32;
  speed = 7;
  damage = 3;
  this->angle = angle;
  directionX = dirX;
  directionY = dirY;
  visible = false;
} 

