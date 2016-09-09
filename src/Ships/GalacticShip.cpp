#include "../../include/Ships/GalacticShip.h"   

#define SPEED 8
  
GalacticShip::GalacticShip() {
  tick = 0;
} 

GalacticShip::~GalacticShip() {
  clean();
} 

void GalacticShip::setTexture() {  
  glBindTexture(GL_TEXTURE_2D, textures[0]);
}

void GalacticShip::defaults() {
  printf("Setting up galatic ship\n");
 
  speed = 7;
 
  health = 30;
  shield = 15;
  
  maxNumWeapons = 3;
  width = 100;
  height = 100;
  
  boostTimer = 0;
  
  textures[0] = txt::LoadTexture("Textures/Game/Ships/GalacticShip.png");
  
  const float mountPosX[maxNumWeapons] = {20, -20, 0};
  const float mountPosY[maxNumWeapons] = {0, 0, 50};
  
  for(int i = 0; i < 2; ++i) {
    switch(i) {
      case 0:
      case 1:   
        WeaponMount.push_back(new BasicMount);
        WeaponMount[i]->setup(BLUEPLASMA);
        WeaponMount[i]->setTimer(BLUEPLASMATIMER - BLUEPLASMATIMER/4);
        WeaponMount[i]->setDamage(2);
        break;
      case 2:
        break;
    }    
    WeaponMount[i]->setOffset(mountPosX[i], mountPosY[i]);
  }
}
    
void GalacticShip::update(float mouseX, float mouseY, float deltaTime, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  if(boostTimer > 50) {
    if(SPEED+extraSpeed > speed) {
      speed+=0.5;
    }
  } else if (boostTimer < 50) {
    if(speed > SPEED) {
      speed-=0.5;
    }
  }
  
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
    
  if(health < crntHealth) {
    crntHealth-=0.000000002;
  }
  
  if(hasBoost) {    
    boostTimer--;
    if(boostTimer <= 0) {
      hasBoost = false;
      extraSpeed = 0;
      speed = SPEED;
    }
  }
}

