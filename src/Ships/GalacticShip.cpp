#include "../../include/Ships/GalacticShip.h"   
  
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
 
  speed = 8;
 
  health = 20;
  shield = 10;
  
  maxNumWeapons = 3;
  width = 100;
  height = 100;
  
  textures[0] = txt::LoadTexture("Textures/Game/Ships/GalacticShip.png");
  
  const float mountPosX[maxNumWeapons] = {20, -20, 0};
  const float mountPosY[maxNumWeapons] = {0, 0, 50};
  
  for(unsigned int i = 0; i < maxNumWeapons; ++i) {
    switch(i) {
      case 0:
      case 1:   
        WeaponMount.push_back(new BasicMount);
        WeaponMount[i]->setup(BLUEPLASMA);
        break;
      case 2:
        WeaponMount.push_back(new TriangleMount);
        WeaponMount[i]->setup(GREENPLASMA);
        break;
    }
    
    WeaponMount[i]->setOffset(mountPosX[i], mountPosY[i]);
  }
}
    
void GalacticShip::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  if(boostTimer > 50) {
    if(5+extraSpeed > speed) {
      speed+=0.5;
    }
  } else if (boostTimer < 50) {
    if(speed > 5) {
      speed-=0.5;
    }
  }
  
  if(tookDamage || shieldDamaged)
    tick--;
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
   
 if(distanceFromCursor > MINIMUM_DISTANCETOSHIP) {
    if(keyState['W'] == BUTTON_DOWN || keyState['w'] == BUTTON_DOWN) {
      y+=speed*directionY;
      x+=speed*directionX;
    } 
  }
  if(keyState['S'] == BUTTON_DOWN || keyState['s'] == BUTTON_DOWN) {
    
    y-=speed*directionY;
    x-=speed*directionX;
  } 
    
  if(keyState['D'] == BUTTON_DOWN || keyState['d'] == BUTTON_DOWN) {
    x+=speed*directionY;
    y-=speed*directionX;
  } else if(keyState['A'] == BUTTON_DOWN || keyState['a'] == BUTTON_DOWN) {
    x-=speed*directionY;
    y+=speed*directionX;
  }  

  if(x < width/2) 
    x = width/2;
  if(x > SPACE_X_RESOLUTION-width/2)
    x = SPACE_X_RESOLUTION-width/2;
  if(y < height/2) 
    y = height/2;
  if(y > SPACE_Y_RESOLUTION-height/2)
    y = SPACE_Y_RESOLUTION-height/2;

  fire(x, y, directionX, directionY, angle, mouseBtnState);
    
  if(health < crntHealth) {
    crntHealth-=0.000000002;
  }
  
  if(hasBoost) {    
    boostTimer--;
    if(boostTimer <= 0) {
      hasBoost = false;
      extraSpeed = 0;
      speed = 5;
    }
  }
}

