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
  buttons[0]->setup(buttonWidth/2+50, 100, buttonWidth, buttonHeight, (char*)"Textures/Menu/Misc/Return.png");
  buttons[0]->drawBorder(true);
  
  // Left Arrow button
  buttons.push_back(new Button);
  buttons[1]->setup(267/3, (SPACE_Y_RESOLUTION/3*2), 57, 133, (char*)"Textures/Menu/Misc/LeftArrow.png");
  buttons[1]->drawBorder(true);
  
  // Right Arrow button
  buttons.push_back(new Button);
  buttons[2]->setup(267*5, (SPACE_Y_RESOLUTION/3*2), 57, 133, (char*)"Textures/Menu/Misc/RightArrow.png");
  buttons[2]->drawBorder(true);  
  
  // 1st Ship Button
  buttons.push_back(new Button);
  buttons[3]->setup(267, SPACE_Y_RESOLUTION/3*2 - 150, 200, 60, 0.3);
  buttons[3]->setText((char*)"Upgrade", 7);
  buttons[3]->drawBorder(true);
  
  // 2nd Ship Button
  buttons.push_back(new Button);
  buttons[4]->setup(720, SPACE_Y_RESOLUTION/3*2 - 150, 200, 60, 0.3);
  buttons[4]->setText((char*)"Buy", 3);
  buttons[4]->drawBorder(true);  
  
  // 3rd Ship Button
  buttons.push_back(new Button);
  buttons[5]->setup(1173, SPACE_Y_RESOLUTION/3*2 - 150, 200, 60, 0.3);
  buttons[5]->setText((char*)"Locked", 6);
  buttons[5]->drawBorder(true);
  
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
  lb.push_back(new Label);
  lb[3]->setup(720, SPACE_Y_RESOLUTION/3*2, 456, 400, (char*)"Textures/Game/Ships/FighterShip1.png");
  lb[3]->setTextureVisiable(false);
  lb[3]->drawBorder(true);
  FShip.VisualSetup(720, SPACE_Y_RESOLUTION/3*2);
  
  // 3rd Ship Box
  lb.push_back(new Label);
  lb[4]->setup(1173, SPACE_Y_RESOLUTION/3*2, 456, 400, (char*)"Textures/Game/Ships/FighterShip1.png");
  lb[4]->setTextureVisiable(false);
  lb[4]->drawBorder(true);
  //FShip.VisualSetup(1173, SPACE_Y_RESOLUTION/3*2);
  
  // 2nd Ship Cost Label
  lb.push_back(new Label);
  lb[5]->setup(720, SPACE_Y_RESOLUTION/3*2 + 150, 0.3);
  lb[5]->setWidth(200);
  lb[5]->setHeight(60);
  lb[5]->setText((char*)"$1000", 5);
  lb[5]->drawBorder(false);
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
  glColor3f(1.0f, 1.0f, 1.0f);

  GShip.draw();
  FShip.draw();

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


 


