#include "../include/Ship.h"   
  
Ship::Ship() {

} 

void Ship::setup() {
  x = 0;
  y = 0;
  width = 100;
  height = 100;
  speed = 5;
  angle = 0;
  directionX = 1;
  directionY = 1; 
  textures[0] = txt::LoadTexture("Textures/Game/Ship.png");
  textures[1] = txt::LoadTexture("Textures/Game/ShipLeft.png");
  textures[2] = txt::LoadTexture("Textures/Game/ShipRight.png");
}
    
void Ship::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
    
  float diffx = mouseX - x;
  float diffy = mouseY - y;
  //diffy /= aspectRatio;
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
    if(keyState[W] == BUTTON_DOWN || keyState[w] == BUTTON_DOWN) {
      y+=speed*directionY;
      x+=speed*directionX;
    } 
  }
  if(keyState[S] == BUTTON_DOWN || keyState[s] == BUTTON_DOWN) {
    
    y-=speed*directionY;
    x-=speed*directionX;
  } 
    
  if(keyState[D] == BUTTON_DOWN || keyState[d] == BUTTON_DOWN) {
    x+=speed*directionY;
    y-=speed*directionX;
  } else if(keyState[A] == BUTTON_DOWN || keyState[a] == BUTTON_DOWN) {
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
}

void Ship::draw() {
  glPushMatrix();
  //angle++;
  glTranslatef(x, y, 0); // M1 - 2nd translation
  glRotatef(angle, 0.0f, 0.0f, 1.0f);  
  glTranslatef(-x, -y, 0); // M1 - 2nd translation
  glEnable(GL_TEXTURE_2D);
  
  glBindTexture(GL_TEXTURE_2D, textures[0]);
  
 // glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x-width/2, y+width/2, 0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x+width/2, y+width/2, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x+width/2, y-width/2, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x-width/2, y-width/2, 0.0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();     
}
    
float Ship::getX() {
  return x;
}

float Ship::getY() {
  return y;
}   

float Ship::getDirectionX() {
  return directionX;
}

float Ship::getDirectionY() {
  return directionY;
}    
    
float Ship::getDistanceFromCursor() {
  return distanceFromCursor;
}
    //float x, y;
    //int health;
    //float speed;
    //float angle;
    //float width, height;
    //float directionX, directionY;   

