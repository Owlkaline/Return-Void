#include "../include/TriangleMount.h"

TriangleMount::TriangleMount() {
  ticks=0;
}

void TriangleMount::setup() { 
  x = -SPACE_X_RESOLUTION;
  y = -SPACE_Y_RESOLUTION;
  angle = 0;
  width = 32;
  height = 32;
  health = 20;
  timer = 14;
  ticks = 0;
  visible = true;
  Texture = txt::LoadTexture("Textures/Game/Weapons/TriangleMount.png");
} 

void TriangleMount::update(float x, float y, float directionX, float directionY, float angle) {  
  float rad = angle* (float)M_PI / 180;
  float newX = (offsetX)*cos(rad) - (offsetY)*sin(rad);
  float newY = (offsetX)*sin(rad) + (offsetY)*cos(rad);
  this->x = x+newX;
  this->y = y+newY;
  this->angle = angle;
  dirX = directionX;
  dirY = directionY;
  
  tick();
    
  for(unsigned int i = 0; i < bullets.size(); ++i) {
    bullets[i]->update();
    if(!bullets[i]->getVisible())
      bullets.erase(bullets.begin() + i);
  }
}

void TriangleMount::addBullet() {
  bullets.push_back(new GreenPlasma);
}

void TriangleMount::reset() {

}
