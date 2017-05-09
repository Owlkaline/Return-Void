#include "../../include/Ships/FighterShip.h"

FighterShip::FighterShip() {
  this->tick = 0;
  this->width = 120;
  this->height = 140;
  
  this->x = SPACE_X_RESOLUTION/2;
  this->y = 100;
  
  this->angle = 0;
    
  // To be removed
  // --------------------------------------------------
  this->coins = 0;
  this->extraSpeed = 0;
  this->specialsLeft = 3;
  this->onCooldown = false;
  this->specialActive = false;
  this->specialTimer = 0;
  this->specialIcon = txt::LoadTexture("Textures/Game/Misc/Boost.png");
  //---------------------------------------------------
  
  this->health = 20;
  this->shield = 5;
  
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
 
  this->speed = 10; 
  
  setTextures();
  this->textures[0] = txt::LoadTexture("Textures/Game/Ships/FighterShip1.png");
  this->textures[1] = txt::LoadTexture("Textures/Game/Ships/FighterShip2.png");
  this->textures[2] = txt::LoadTexture("Textures/Game/Ships/FighterShip3.png");

  WeaponMount.push_back(new MountType2(30, 5));
  WeaponMount.push_back(new MountType2(-30, 5)); 
}

FighterShip::~FighterShip() {
  clean();
}

void FighterShip::setTexture() {
  if(tookDamage)
    glColor3f(1.0, 0.0, 0.0);
  glBindTexture(GL_TEXTURE_2D, textures[crntTexture]);
}

void FighterShip::update(float mouseX, float mouseY, float deltaTime, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  animate();

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
  // w
  if(keyState[87] == BUTTON_DOWN) {
    y+=speed*deltaTime;
  } else if(keyState[83] == BUTTON_DOWN) { //s
    y-=speed*deltaTime;
  }
  //d
  if(keyState[68] == BUTTON_DOWN) {
    x+=speed*deltaTime;
  } else if(keyState[65] == BUTTON_DOWN) {// a
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

  if(health < crntHealth) {
    crntHealth-=0.000000002;
  }
}

