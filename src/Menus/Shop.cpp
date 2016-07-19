#include "../../include/Menus/Shop.h"

Shop::Shop() {

}

void Shop::setup() {
  ended = false;
  type = MAINMENU;
  pos = 0;
  numShips = 0;
  selected = profile.getSelectedShip();
  
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
  
  // Top Left Shop Name Box
  lb.push_back(new Label);
  lb[0]->setup(BUTTONWIDTH/4 * 3, SPACE_Y_RESOLUTION - 100, BUTTONWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/MainMenu/Shop.png");
  lb[0]->fill(0.0, 0.0, 1.0f);
  lb[0]->drawBorder(true);
  
  // Description Box
  lb.push_back(new Label);
  lb[1]->setup(540, SPACE_Y_RESOLUTION/3, 0.3);
  lb[1]->setText((char*)"Description", 11);
  lb[1]->setWidth(1000);
  lb[1]->setHeight(300);
  lb[1]->fill(0.6, 0.6, 0.6);
  lb[1]->drawBorder(true);
  
  coins = profile.getCoins();
  
  std::stringstream ss;
  ss << coins;
  std::string strCoins = "Coins: " + ss.str();
  
  // Coin Box
  lb.push_back(new Label);
  lb[2]->setup(SPACE_X_RESOLUTION - 200, SPACE_Y_RESOLUTION-100, 0.3);
  lb[2]->setText(strCoins.c_str(), strCoins.length() + 1);
  lb[2]->setWidth(350);
  lb[2]->setHeight(70);
  lb[2]->fill(0.6, 0.6, 0.6);
  lb[2]->drawBorder(true);
  
  // Left Arrow button Selected Ship
  buttons.push_back(new Button);
  buttons[3]->setup(1676-200+ARROWWIDTH, 390, ARROWWIDTH, 133, (char*)"Textures/Menu/Misc/LeftArrow.png");
  buttons[3]->drawBorder(true);
  if(selected == 0) {
    buttons[3]->disable();
    buttons[3]->setVisible(false);
  }
  
  // Right Arrow button Selected Ship
  buttons.push_back(new Button);
  buttons[4]->setup(1676+200-ARROWWIDTH, 390, ARROWWIDTH, 133, (char*)"Textures/Menu/Misc/RightArrow.png");
  buttons[4]->drawBorder(true);  

  for(int i = 0; i < 6; ++i) {
    if(profile.getShipsBought(i) == true)
      numShips++;
  }
  
  bool unlocked;
  bool bought;

  for(int i = 0; i < 6; ++i) {
    
    unlocked = profile.getShipsUnlocked(i);
    bought = profile.getShipsBought(i);
    if(unlocked && bought) {
      shipType[i] = true;
    } else {
      shipType[i] = false;
    }
    box.push_back(new Shipbox); 
    switch(i) {
      case 0:
        box[i]->setup(267 + 453*i, SPACE_Y_RESOLUTION/3*2, unlocked, bought, GALACTICSHIP);
        break;
      case 1:
        box[i]->setup(267 + 453*i, SPACE_Y_RESOLUTION/3*2, unlocked, bought, FIGHTERSHIP);
        break;
      case 2: 
      case 3:
      case 4:
      case 5:
       box[i]->setup(267 + 453*i, SPACE_Y_RESOLUTION/3*2, unlocked, bought, NOTHING);
       break;
    }
  }
  
  int more = false;
  for(int i = selected+1; i < 6; ++i) {
    if(shipType[i])
      more = true;
  }
  if(!more) { 
    buttons[4]->disable();
    buttons[4]->setVisible(false);  
  }      
  
  box.push_back(new Shipbox);
  switch(selected) {
    case 0:
      box[box.size()-1]->setup(1676, 390, GALACTICSHIP);
      break;
    case 1:
      box[box.size()-1]->setup(1676, 390, FIGHTERSHIP);
      break;
    case 2:
    case 3:
    case 4:
    case 5:
      box[box.size()-1]->setup(1676, 390, GALACTICSHIP);
      break;
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
    for(unsigned int i = 0; i < 6; ++i) {
      if(box[i]->AttemptBuy()) {
        if(coins >= box[i]->getCost()) {
          box[i]->buy();
          coins-=box[i]->getCost();
          std::stringstream ss;
          ss << coins;
          std::string strCoins = "Coins: " + ss.str();
          lb[2]->setText(strCoins.c_str(), strCoins.length() + 1);
          numShips++;
          buttons[4]->enable();
          buttons[4]->setVisible(true);
          shipType[i] = true;
        }
      }
    }
    
    //Left Arrow Shop
    if(buttons[1]->Clicked()) {
      if(pos != 0) {
        pos--;
        buttons[2]->enable();
        buttons[2]->setVisible(true);        
        if(pos == 0) {          
          buttons[1]->disable();
          buttons[1]->setVisible(false);
        }
        for(unsigned int i = 0; i < 6; ++i)
          box[i]->moveRight();
      } else {
        buttons[1]->disable();
        buttons[1]->setVisible(false);
      }   
    }
    
    //Right Arrow Shop
    if(buttons[2]->Clicked()) {
      if(pos != 5) {
        pos++;
        buttons[1]->enable();
        buttons[1]->setVisible(true);        
        if(pos == 5) {          
          buttons[2]->disable();
          buttons[2]->setVisible(false);
        }
        for(unsigned int i = 0; i < 6; ++i)
          box[i]->moveLeft();
      } else {        
        buttons[2]->disable();
        buttons[2]->setVisible(false);
      }
    }
    
    // Left Arrow Selection
    if(buttons[3]->Clicked()) {
      if(selected != 0) {
        for(int i = selected-1; i >= 0; --i) {
          if(shipType[i]) {
            selected = i;
            switch(selected) {              
              case 0:
                box[box.size()-1]->setShip(GALACTICSHIP);
                buttons[3]->disable();
                buttons[3]->setVisible(false);
                break;
              case 1:
                box[box.size()-1]->setShip(FIGHTERSHIP);
                break;
              case 2:
              case 3:
              case 4:
                box[box.size()-1]->setShip(GALACTICSHIP);
                break;
            }
            break;
          }
        }
      }
      buttons[4]->enable();
      buttons[4]->setVisible(true);
    }
    
    // Right Arrow Selection
    if(buttons[4]->Clicked()) {
      if(selected != 5) {
        for(int i = selected+1; i < 6; ++i) {
          if(shipType[i]) {
            selected = i;
            switch(selected) {              
              case 1:
                box[box.size()-1]->setShip(FIGHTERSHIP);
                break;
              case 2:
              case 3:
              case 4:
              case 5:
                box[box.size()-1]->setShip(GALACTICSHIP);
                buttons[4]->disable();
                buttons[4]->setVisible(false);  
                break;
            }
            break;
          }
        }
        int more = false;
        for(int i = selected+1; i < 6; ++i) {
          if(shipType[i])
            more = true;
        }
        if(!more) { 
          buttons[4]->disable();
          buttons[4]->setVisible(false);  
        }        
        buttons[3]->enable();
        buttons[3]->setVisible(true);
      }
    }
  }
}

void Shop::drawAfter() {

}

void Shop::save() {
  for(unsigned int i = 0; i < 6; ++i) {
    profile.setShipsUnlocked(i, box[i]->getUnlocked());
    profile.setShipsBought(i, box[i]->getBought());
  }
  profile.setSelectedShip(selected);
  profile.setCoins(coins);
  profile.Save();
} 


