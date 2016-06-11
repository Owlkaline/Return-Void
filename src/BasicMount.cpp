#include "../include/BasicMount.h"

BasicMount::BasicMount() {
ticks=0;
}

void BasicMount::setup(int variant) { 
  x = -SPACE_X_RESOLUTION;
  y = -SPACE_Y_RESOLUTION;
  angle = 0;
  width = 8;
  height = 64;
  health = 10;
  ticks = 0;
  visible = true;
  this->variant = variant;
  switch (variant) {
    case BLUEPLASMA:
      timer = 7;
      break;
    case REDPLASMA:
      timer = 20;
      break;
  }
  Texture = txt::LoadTexture("Textures/Game/Weapons/BasicMount.png");
  
} 

void BasicMount::setup() { 
  setup(BLUEPLASMA);
}

void BasicMount::update(float x, float y, float directionX, float directionY, float angle) {  
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

void BasicMount::addBullet() {
  switch(variant) {
    case BLUEPLASMA:
      bullets.push_back(new BluePlasma);
      break;
    case REDPLASMA:
      bullets.push_back(new RedPlasma);
      break;
  }
}

void BasicMount::reset() {

}
