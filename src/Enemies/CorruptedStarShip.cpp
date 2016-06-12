#include "../../include/Enemies/CorruptedStarShip.h"

void CorruptedStarShip::setup() {
  width = 75;
  height = 75;
  health = 10;
  maxWeaponMounts = 1;
  visible = true;
  speed = 5;
  x = -SPACE_X_RESOLUTION;
  y = -SPACE_X_RESOLUTION;
  Texture = txt::LoadTexture("Textures/Game/Enemies/CorruptedStarShip.png");
  for(int i = 0; i < maxWeaponMounts; ++i) {
    WeaponMount.push_back(new BasicMount);
    WeaponMount[i]->setup(REDPLASMA);
    WeaponMount[i]->setOffset(0, 20);
  }
}
  
void CorruptedStarShip::update() {
  y-=speed;
  if(y <= -height)
    setVisible(false);
  
  for(int i = 0; i < maxWeaponMounts; ++i) {
    if(!visible)
      WeaponMount[i]->setVisible(false);
    WeaponMount[i]->update(x, y, 0, -1, 180); 
  }  
}
 
void CorruptedStarShip::reset() {

}

void CorruptedStarShip::draw() {
  for(int i = 0; i < maxWeaponMounts; ++i) 
    WeaponMount[i]->draw();
    
  if(visible) {
    glEnable(GL_TEXTURE_2D); 
    glBindTexture(GL_TEXTURE_2D, Texture);
  
    // glColor3f(0.0, 0.0, 1.0);
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
  } 
}
