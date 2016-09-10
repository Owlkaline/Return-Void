#include "../../include/Misc/SmallExplosion.h"
    
SmallExplosion::SmallExplosion() {
  this->expired = false;
  
  this->timer = 0;
  this->size = 30;
  this->pos[0] = 0;
  this->pos[1] = 0;
  this->dirX = 0;
  this->dirY = 0;
  this->texture = txt::LoadTexture("Textures/Game/Misc/explo1.png");
}

SmallExplosion::~SmallExplosion() {
  texture = 0;
}

void SmallExplosion::setup(float x, float y, float dirX, float dirY) {
  this->pos[0] = x;
  this->pos[1] = y;
  this->timer = 10;
  this->dirX = dirX;
  this->dirY = dirY;
  this->pos[0] += dirX*10;
  this->pos[1] += dirY*10;
}
   
void SmallExplosion::draw() {
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(pos[0] - size/2, pos[1] - size/2, 0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(pos[0] + size/2, pos[1] - size/2, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(pos[0] + size/2, pos[1] + size/2, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(pos[0] - size/2, pos[1] + size/2, 0.0);
  glEnd();

  glDisable(GL_TEXTURE_2D);
}

void SmallExplosion::update(float deltaTime) {
  pos[0] += dirX*deltaTime;
  pos[1] += dirY*deltaTime;
  if(!expired) {
    timer -= 1*deltaTime;
    if(timer < 0)
      expired = true;
  }
}
  
bool SmallExplosion::hasExpired() { return expired; }
    


