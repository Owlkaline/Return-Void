#include "../../include/Menus/Shop.h"

Shop::Shop() {

}

void Shop::setup() {
  ended = false;
  type = MAINMENU;
  
  // Buttons
  float buttonWidth = 267;
  float buttonHeight = 95;

  buttons.push_back(new Button);
  buttons[0]->setup(buttonWidth/2+50, 100, buttonWidth, buttonHeight, (char*)"Textures/Menu/Return.png");
  buttons[0]->drawBorder(true);
  
  // Top Left Name Box
  lb.push_back(new Label);
  lb[0]->setup(190, SPACE_Y_RESOLUTION - 100, 0.3);
  lb[0]->setText((char*)"Shop", 4);
  lb[0]->setWidth(300);
  lb[0]->setHeight(70);
  lb[0]->drawBorder(true);
  
  // Description Box
  lb.push_back(new Label);
  lb[1]->setup(540, SPACE_Y_RESOLUTION/3, 0.3);
  lb[1]->setText((char*)"Desciption dark delicous duck dick for din", 42);
  lb[1]->setWidth(1000);
  lb[1]->setHeight(300);
  lb[1]->drawBorder(true);
  
  // 1st Ship Box
  lb.push_back(new Label);
  lb[2]->setup(267, SPACE_Y_RESOLUTION/3*2, 456, 400, (char*)"Textures/Game/Ships/GalacticShip.png");
  lb[2]->setTextureVisiable(false);
  lb[2]->drawBorder(true);
  GShip.VisualSetup(267, SPACE_Y_RESOLUTION/3*2);
  
  // 2nd Ship Box
  FShip.VisualSetup(720, SPACE_Y_RESOLUTION/3*2);
}

void Shop::restart() {

}

void Shop::drawBackground() {
  glColor3f(0.5f, 0.5f, 0.5f);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, SPACE_Y_RESOLUTION, 0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(SPACE_X_RESOLUTION, SPACE_Y_RESOLUTION, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(SPACE_X_RESOLUTION, 0, 0.0);   
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0, 0, 0.0);
  glEnd();
  
  // Return Box
  
  //drawBox(buttons[0]->getX(), buttons[0]->getY(), buttons[0]->getWidth()/2, buttons[0]->getHeight()/2);
  
  // Top Left Name Box
 // drawBox(267, SPACE_Y_RESOLUTION - 100, 230, 50);
  
   // 1st Ship box
  float width = 456;
  float height = 400;
  float x = 267;
  float y = (SPACE_Y_RESOLUTION/3*2);
  drawBox(x, y, width/2, height/2);
  
  // 2st Ship box
  x += width;
  drawBox(x, y, width/2, height/2); 
  
  // 3st Ship box
  x += width;
  drawBox(x, y, width/2, height/2); 
  
  GShip.draw();
  FShip.draw();
  
  // Left arrow box
  width /= 8;
  height /= 3;
  x = 267/3;
  y = (SPACE_Y_RESOLUTION/3*2);
  drawBox(x, y, width/2, height/2);
  
  // Right arrow box
  x *= 3 * 5;
  drawBox(x, y, width/2, height/2);
  
  // Description Box
 /* width = 1000;
  height = 300; 
  x = 540;
  y = SPACE_Y_RESOLUTION/3;
  drawBox(x, y, width/2, height/2);*/
  
 /* // Left arrow Box
  width = 30;
  height = 70;
  x = 100;
  y = (SPACE_Y_RESOLUTION-360);
  drawBox(x, y, width, height);
  
  // Right arrow Box
  width = 30;
  height = 70;
  x = 1200;
  y = (SPACE_Y_RESOLUTION-360);
  drawBox(x, y, width, height);*/

}

void Shop::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
    prevKeyState[ESC] = keyState[ESC];
    type = MAINMENU;
    ended = true;
  }

  for(unsigned int i = 0; i < buttons.size(); ++i)
    buttons[i]->update(mouseX, mouseY, mouseBtnState, prevMouseBtnState);
  
  if(buttons[0]->Clicked()) {
    type = MAINMENU;
    ended = true;
  } 
}

void Shop::drawBox(float x, float y, float width, float height) {
  float border = 5;
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);

    // Left
    glVertex3f(x-width, y+height, 0.0);
    glVertex3f(x-width+border, y+height, 0.0);
    glVertex3f(x-width+border, y-height, 0.0);
    glVertex3f(x-width, y-height, 0.0);

    // Right
    glVertex3f(x+width, y+height, 0.0);
    glVertex3f(x+width-border, y+height, 0.0);
    glVertex3f(x+width-border, y-height, 0.0);
    glVertex3f(x+width, y-height, 0.0);

    // top
    glVertex3f(x+width, y+height, 0.0);
    glVertex3f(x+width, y+height-border, 0.0);
    glVertex3f(x-width, y+height-border, 0.0);
    glVertex3f(x-width, y+height, 0.0);

    // bottom
    glVertex3f(x+width, y-height, 0.0);
    glVertex3f(x+width, y-height+border, 0.0);
    glVertex3f(x-width, y-height+border, 0.0);
    glVertex3f(x-width, y-height, 0.0);

  glEnd();
  glColor3f(1.0, 1.0, 1.0);
}


 


