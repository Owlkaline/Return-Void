#include "../../include/Mounts/MountType2.h"

MountType2::MountType2(float offsetX, float offsetY) { 
    this->currentTexture = 0;
    this->bulletTicks = 0;
    this->damageTicks = 0;
    this->damageTimer = 0;
    this->visible = true;
    this->tookDamage = false;
    this->automated = true; 
    
    this->angle = 0; 
    this->dirX = 0;
    this->dirY = 0;  
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    this->x = -10;
    this->y = -10;
    this->width = 32;
    this->height = 32;

    this->bulletType = PURPLEPLASMA;
    
    setTimers();
    
    //Load texture
    //getPurpleMountTexture();
}

void MountType2::reset(float x, float y) {
  this->visible = true;
  this->tookDamage = false;
  this->x = x+offsetX;
  this->y = y+offsetY;
  
  setTimers();
}

std::string MountType2::getTexture() {
  if(currentTexture == 0) {
    return "PurpleMount"; //glBindTexture(GL_TEXTURE_2D, getPurpleMountTexture());
  } 
}
