#include "../../include/Ships/GalacticShip.h"   
  
GalacticShip::GalacticShip() {
  tick = 0;
} 

void GalacticShip::draw() {
  if(visible){

    glPushMatrix();
    if(tookDamage) {
      tick--;
        if(tick <= 0)
          tookDamage = false;
        glColor3f(1.0, 0.0, 0.0);
    }
    glTranslatef(x, y, 0); // M1 - 2nd translation
    glRotatef(angle, 0.0f, 0.0f, 1.0f);  
    glTranslatef(-x, -y, 0); // M1 - 2nd translation
    glEnable(GL_TEXTURE_2D);
  
    glBindTexture(GL_TEXTURE_2D, textures[0]);
  
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(x-width/2, y+height/2, 0.0);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(x+width/2, y+height/2, 0.0);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(x+width/2, y-height/2, 0.0);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(x-width/2, y-height/2, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();  
    glColor4f(1.0, 1.0, 1.0, 1.0);      

  }
  
  for(unsigned int i = 0; i < WeaponMount.size(); ++i) 
    WeaponMount[i]->draw(); 
    
  if(shield > 0)
    drawShield();
}

void GalacticShip::setup() {
  x = SPACE_X_RESOLUTION/2;
  y = 100;
  
  coins = 0;
  speed = 5;
  angle = 0;
  health = 20;
  shield = 10;
  extraSpeed = 0;
  maxShield = shield;
  maxHealth = health;
  crntHealth = health;
  maxNumWeapons = 3;
  width = 100;
  height = 100;
  hasBoost = false;
  visible = true;
  tookDamage = false;
  shieldDamaged = false;
  directionX = 1;
  directionY = 1; 
  
  textures[0] = txt::LoadTexture("Textures/Game/Ships/GalacticShip.png");
  
  healthBarTexture[0] = txt::LoadTexture("Textures/Game/Misc/HealthBarBase.png");
  healthBarTexture[1] = txt::LoadTexture("Textures/Game/Misc/HealthBar.png");
  healthBarTexture[2] = txt::LoadTexture("Textures/Game/Misc/ShieldBar.png");
  
  shieldTexture[0] = txt::LoadTexture("Textures/Game/Ships/Shield.png");
  shieldTexture[1] = txt::LoadTexture("Textures/Game/Ships/ShieldRipple1.png");
  shieldTexture[2] = txt::LoadTexture("Textures/Game/Ships/ShieldRipple2.png");
  shieldTexture[3] = txt::LoadTexture("Textures/Game/Ships/ShieldRipple3.png");
  shieldTexture[4] = txt::LoadTexture("Textures/Game/Ships/ShieldRipple4.png");
  shieldTexture[5] = txt::LoadTexture("Textures/Game/Ships/ShieldRipple5.png");
  
  const float mountPosX[maxNumWeapons] = {20, -20, 0};
  const float mountPosY[maxNumWeapons] = {0, 0, 50};
  
  for(unsigned int i = 0; i < WeaponMount.size(); ++i) {
    switch(i) {
      case 0:
      case 1:   
        WeaponMount.push_back(new BasicMount);
        WeaponMount[i]->setup(BLUEPLASMA);
        break;
      case 2:
        WeaponMount.push_back(new TriangleMount);
        WeaponMount[i]->setup();
        break;
    }
    
    WeaponMount[i]->setOffset(mountPosX[i], mountPosY[i]);
  }
}

void GalacticShip::clean() {
    for(unsigned int i = 0; i < WeaponMount.size(); ++i) {
      WeaponMount[i]->clean();
     // delete WeaponMount[i];
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
    
    
  for(unsigned int i = 0; i < WeaponMount.size(); ++i) 
    WeaponMount[i]->update(x, y, directionX, directionY, angle);
    
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

