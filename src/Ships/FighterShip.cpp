#include "../../include/Ships/FighterShip.h"   
  
FighterShip::FighterShip() {
  tick = 0;
} 

FighterShip::~FighterShip() {
  clean();
} 

void FighterShip::setTexture() {
  if(tookDamage) 
    glColor3f(1.0, 0.0, 0.0);
  glBindTexture(GL_TEXTURE_2D, textures[crntTexture]);
}

void FighterShip::defaults() {
  printf("Setting up fighter ship\n");  
 
  speed = 10;
  health = 15;
  shield = 5;
 
  maxNumWeapons = 2;
  width = 120;
  height = 140;
  
  textures[0] = txt::LoadTexture("Textures/Game/Ships/FighterShip1.png");
  textures[1] = txt::LoadTexture("Textures/Game/Ships/FighterShip2.png");
  textures[2] = txt::LoadTexture("Textures/Game/Ships/FighterShip3.png");
  
  const float mountPosX[maxNumWeapons] = {30, -30};
  const float mountPosY[maxNumWeapons] = {5, 5};
  for(int i = 0; i < maxNumWeapons; ++i) {
    switch(i) {
      case 0:
      case 1:   
        WeaponMount.push_back(new PurpleMount);
        WeaponMount[i]->setup(PURPLEPLASMA);
        break;
    }    
    WeaponMount[i]->setOffset(mountPosX[i], mountPosY[i]);
  }
}
    
void FighterShip::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  animate();
  
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
}

