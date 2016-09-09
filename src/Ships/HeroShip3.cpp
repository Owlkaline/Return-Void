#include "../../include/Ships/HeroShip3.h"   
  
HeroShip3::HeroShip3() {
  tick = 0;
} 

HeroShip3::~HeroShip3() {
  clean();
} 

void HeroShip3::setTexture() {  
  glBindTexture(GL_TEXTURE_2D, textures[crntTexture]);
}

void HeroShip3::defaults() {
  printf("Setting up galatic ship\n");
 
  speed = 9;
 
  health = 40;
  shield = 5;
  
  maxNumWeapons = 1;
  width = 100;
  height = 100;
  
  textures[0] = txt::LoadTexture("Textures/Game/Ships/HeroShip3.png");
  textures[1] = txt::LoadTexture("Textures/Game/Ships/HeroShip3C1.png");
  textures[2] = txt::LoadTexture("Textures/Game/Ships/HeroShip3C2.png");
  textures[3] = txt::LoadTexture("Textures/Game/Ships/HeroShip3C3.png");
  crntTexture = 0;
  
  const float mountPosX[maxNumWeapons] = {0};
  const float mountPosY[maxNumWeapons] = {50};
  WeaponMount.push_back(new TriangleMount);
  WeaponMount[0]->setup(GREENPLASMA);        
  WeaponMount[0]->setDamage(9);
  WeaponMount[0]->setTimer(70);
  WeaponMount[0]->setOffset(mountPosX[0], mountPosY[0]);
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
    crntTexture = 3;
  } else if (charge > 40) {
    crntTexture = 2;
  } else if (charge > 20) {
    crntTexture = 1;
  } else {
    crntTexture = 0;
  }
    
  if(health < crntHealth) {
    crntHealth-=0.000000002;
  }
}

