#include "../../include/Ships/HeroShip3.h"   
  
HeroShip3::HeroShip3() {
  this->tick = 0;
  this->width = 100;
  this->height = 100;
  
  this->x = SPACE_X_RESOLUTION/2;
  this->y = 100;
  
  this->angle = 0;
    
  // To be removed
  // --------------------------------------------------
  this->onCooldown = false;
  this->coins = 0;
  this->extraSpeed = 0;
  this->specialsLeft = 3;
  this->specialActive = false;
  this->specialTimer = 0;
  //---------------------------------------------------
  
  this->health = 40;
  this->shield = 0;
  
  this->maxShield = shield;
  this->maxHealth = health;
  this->crntHealth = health;
  
  this->visible = true;
  this->tookDamage = false;
  this->shieldDamaged = false;
  
  this->directionX = 1;
  this->directionY = 1; 
  
  this->crntTexture = 0;
      
  printf("Setting up galatic ship\n");
 
  this->speed = 9; 

  maxNumWeapons = 1;

  this->crntTexture = 0;
  WeaponMount.push_back(new MountType3(0, 0));       
  WeaponMount[0]->setDamage(9);
} 

HeroShip3::~HeroShip3() {
  clean();
} 

std::string HeroShip3::getTexture() {  
//  glBindTexture(GL_TEXTURE_2D, textures[crntTexture]);
  std::string str = "HeroShip";
  return str;
}

void HeroShip3::special() { 
  if(!specialActive) {
    specialActive = true; 
    specialTimer = 600; 
    maxShield = 20;
    shield = 20;
  }
}
    
void HeroShip3::update(float mouseX, float mouseY, float deltaTime, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  
  if(tookDamage || shieldDamaged)
    tick-=1*deltaTime;
    
  float diffx = mouseX - x;
  float diffy = mouseY - y;
  
  distanceFromCursor = pow(pow(diffy,2.0f) + pow(diffx,2.0f), 0.5f);
  directionX = (diffx) / (distanceFromCursor);
  directionY = (diffy) / distanceFromCursor;//*aspectRatio) / (distance);
 
  if (diffx > 0.0 && diffy > 0.0) {//Quadrant 1
    angle = (float)atan(diffy/diffx) *180.0f / (float)M_PI ;
    angle = angle - 90.0f;
  }else if(diffx < 0 && diffy > 0) {//Quadrant 2
    angle = (float)atan(diffy/diffx) *180.0f / (float)M_PI ;
    angle = angle + 90.0f;
  } else     if(diffx < 0 && diffy < 0) {//Quadrant 3
     angle = (float)atan(diffy/diffx) *180.0f / (float)M_PI ;
     angle = angle+90.0f;
  } else     if(diffx > 0 && diffy < 0) {//Quadrant 4
     angle = (float)atan(diffy/diffx) * 180.0f / (float)M_PI ;
     angle = angle - 90.0f;
  }
  
  // Space bar
  if(keyState[32] == BUTTON_DOWN && prevKeyState[32] == BUTTON_UP) {
    if(!specialActive && !onCooldown)
      special();
  }
   
  if(keyState[87] == BUTTON_DOWN) {
    y+=speed*deltaTime;
  } else if(keyState[83] == BUTTON_DOWN) {
    y-=speed*deltaTime;
  }

  if(keyState[68] == BUTTON_DOWN) {
    x+=speed*deltaTime;
  } else if(keyState[65] == BUTTON_DOWN) {
    x-=speed*deltaTime;
  }

  if(x < width/2) 
    x = width/2;
  if(x > SPACE_X_RESOLUTION-width/2)
    x = SPACE_X_RESOLUTION-width/2;
  if(y < height/2) 
    y = height/2;
  if(y > SPACE_Y_RESOLUTION-height/2)
    y = SPACE_Y_RESOLUTION-height/2;

  fire(x, y, deltaTime, directionX, directionY, angle, mouseBtnState);
  
  int charge = WeaponMount[0]->getTimer();
  if(charge > 60) {
    crntTexture = 0;
  } else if (charge > 40) {
    crntTexture = 0;
  } else if (charge > 20) {
    crntTexture = 0;
  } else {
    crntTexture = 0;
  }
  
  if(specialActive) {    
    specialTimer-=1*deltaTime;
    if(specialTimer <= 0) {
      onCooldown = true;
      specialTimer = 1000;
      specialActive = false;
      shield = 0;
      maxShield = 0;
      specialsLeft = 0;
    }
  }
  if(onCooldown) {
    specialTimer-=1*deltaTime;
    if(specialTimer <= 0) {
      onCooldown = false;
      specialsLeft = 1;
    }
  }
    
  if(health < crntHealth) {
    crntHealth-=0.000000002;
  }
}

