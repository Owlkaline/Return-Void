#include "../../include/Menus/Shop.h"

Shop::Shop() {

}

void Shop::setup() {
  ended = false;
  type = MAINMENU;
  pos = 0;
  
  profile.Load();
  
  // Buttons
  // Return button
  buttons.push_back(new Button);
  buttons[0]->setup(BUTTONWIDTH/2+50, 100, BUTTONWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/Misc/Return.png");
  buttons[0]->drawBorder(false);
  
  // Left Arrow button
  buttons.push_back(new Button);
  buttons[1]->setup(267/3, (SPACE_Y_RESOLUTION/3*2), ARROWWIDTH, 133, (char*)"Textures/Menu/Misc/LeftArrow.png");
  buttons[1]->drawBorder(true);
  buttons[1]->disable();
  buttons[1]->setVisible(false);
  
  // Right Arrow button
  buttons.push_back(new Button);
  buttons[2]->setup(267*5, (SPACE_Y_RESOLUTION/3*2), ARROWWIDTH, 133, (char*)"Textures/Menu/Misc/RightArrow.png");
  buttons[2]->drawBorder(true);  
  
  // Top Left Name Box
  lb.push_back(new Label);
  lb[0]->setup(BUTTONWIDTH/4 * 3, SPACE_Y_RESOLUTION - 100, BUTTONWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/MainMenu/Shop.png");
  lb[0]->fill(1.0, 1.0, 1.0f);
  lb[0]->drawBorder(true);
  
  // Description Box
  lb.push_back(new Label);
  lb[1]->setup(540, SPACE_Y_RESOLUTION/3, 0.3);
  lb[1]->setText((char*)"Desciption dark delicous duck dick for din", 42);
  lb[1]->setWidth(1000);
  lb[1]->setHeight(300);
  lb[1]->fill(0.6, 0.6, 0.6);
  lb[1]->drawBorder(true);
  
  coins = profile.getCoins();
  
  std::stringstream ss;
  ss << coins;
  std::string strCoins = "Coins: $" + ss.str();
  
  // Coin Box
  lb.push_back(new Label);
  lb[2]->setup(SPACE_X_RESOLUTION - 200, SPACE_Y_RESOLUTION-100, 0.3);
  lb[2]->setText(strCoins.c_str(), strCoins.length() + 1);
  lb[2]->setWidth(350);
  lb[2]->setHeight(70);
  lb[2]->fill(1.0, 1.0, 1.0);
  lb[2]->drawBorder(true);
  
  bool unlocked;
  bool bought;

  for(int i = 0; i < 6; ++i) {
    unlocked = profile.getShipsUnlocked(i);
    bought = profile.getShipsBought(i);
    box.push_back(new Shipbox); 
    box[i]->setup(267 + 453*i, SPACE_Y_RESOLUTION/3*2, unlocked, bought, i);
  }
  
  background = txt::LoadTexture((char*)"Textures/Menu/ShopMenu/Background.png");
}

void Shop::restart() {

}

void Shop::drawBackground() {  
  glColor3f(1.0f, 1.0f, 1.0f);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, background);
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
  glDisable(GL_TEXTURE_2D);
  
  for(unsigned int i = 0; i < box.size(); ++i)
    box[i]->draw();
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
    save();
    type = MAINMENU;
    ended = true;
  } 
  
  for(unsigned int i = 0; i < box.size(); ++i)
    box[i]->update(mouseX, mouseY, mouseBtnState, prevMouseBtnState);
 
  if(!box[0]->checkIfMoving()) {
    //Left Arrow
    if(buttons[1]->Clicked()) {
      if(pos != 0) {
        pos--;
        buttons[2]->enable();
        buttons[2]->setVisible(true);        
        if(pos == 0) {          
          buttons[1]->disable();
          buttons[1]->setVisible(false);
        }
        for(unsigned int i = 0; i < box.size(); ++i)
          box[i]->moveRight();
      } else {
        buttons[1]->disable();
        buttons[1]->setVisible(false);
      }   
    }
    //Right Arrow
    if(buttons[2]->Clicked()) {
      if(pos != 5) {
        pos++;
        buttons[1]->enable();
        buttons[1]->setVisible(true);
        
        if(pos == 5) {          
          buttons[2]->disable();
          buttons[2]->setVisible(false);
        }
        for(unsigned int i = 0; i < box.size(); ++i)
          box[i]->moveLeft();
      } else {        
        buttons[2]->disable();
        buttons[2]->setVisible(false);
      }
    }
  }
}

void Shop::drawAfter() {

}

void Shop::save() {
  for(unsigned int i = 0; i < box.size(); ++i) {
    profile.setShipsUnlocked(i, box[i]->getUnlocked());
    profile.setShipsBought(i, box[i]->getBought());
  }
  profile.setCoins(coins);
  profile.Save();
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


 


