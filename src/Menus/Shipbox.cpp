#include "../../include/Menus/Shipbox.h"

Shipbox::~Shipbox() {
  clean();
}

void Shipbox::setup(float x, float y, int shipType) {
  this->x = x;
  this->y = y;
  this->shipType = shipType;
  isMovingLeft = false;
  isMovingRight = false;
  visible = true;
  selected = true;
  switch(shipType) {
    case GALACTICSHIP:
      ship.push_back(new GalacticShip);
      break;
    case FIGHTERSHIP:
      ship.push_back(new FighterShip);
      break;
    case NOTHING:
      break;
    default:
      printf("Error in Shipbox.cpp: Unkown ship varient: %d", shipType);
      exit(0);
      break;
  }
  for(unsigned int i = 0; i < ship.size(); ++i)
    ship[i]->VisualSetup(x, y);
    
  // Select Ship Box
  lb.push_back(new Label);
  lb[0]->setup(x, y, 400, 400, (char*)"Textures/Menu/ShopMenu/Boxbackground.png");
  lb[0]->drawBorder(true);
  
  Settings *settings = Settings::instance();
  float width = settings->getCurrentWindowWidth();
  float height = settings->getCurrentWindowHeight();
  float ratioX = width/(float)SPACE_X_RESOLUTION;
  float ratioY = height/(float)SPACE_Y_RESOLUTION;
  
  // Selected Ship Name
  lb.push_back(new Label);
  lb[1]->setup(x, y+135, 30*ratioX, 30*ratioY);
  lb[1]->setText("Select Ship", 11);
  lb[1]->setColour(0.0, 0.0, 0.0);
  lb[1]->setWidth(350);
  lb[1]->setHeight(70);
  lb[1]->fill(0.6, 0.6, 0.6);
  lb[1]->drawBorder(true);
  
}

void Shipbox::setup(float x, float y, bool unlocked, bool bought, int shipType) {
  this->x = x;
  this->y = y;
  this->shipType = shipType;
  this->unlocked = unlocked;
  this->bought = bought;
  selected = false;
  isMovingLeft = false;
  isMovingRight = false;
  attemptBuy = false;
  visible = true;
  
  Settings *settings = Settings::instance();
  float width = settings->getCurrentWindowWidth();
  float height = settings->getCurrentWindowHeight();
  float ratioX = width/(float)SPACE_X_RESOLUTION;
  float ratioY = height/(float)SPACE_Y_RESOLUTION;
  
  cost = 0;

  oldX = x;
  switch(shipType) {
    case GALACTICSHIP:
      ship.push_back(new GalacticShip);
      break;
    case FIGHTERSHIP:
      ship.push_back(new FighterShip);
      break;
    case NOTHING:
      break;
    default:
      printf("Error in Shipbox.cpp: Unkown ship varient: %d", shipType);
      exit(0);
      break;
  }
  
  for(unsigned int i = 0; i < ship.size(); ++i)
    ship[i]->VisualSetup(x, y);
  
  // 1st Ship Box
  lb.push_back(new Label);
  lb[0]->setup(x, y, 456, 400, (char*)"Textures/Menu/ShopMenu/Boxbackground.png");
  lb[0]->drawBorder(true);
  
  buttons.push_back(new Button);
  buttons[0]->setup(x, y - 150, 200, 60, 30*ratioX, 30*ratioY);
  
  if(unlocked) {
    if(bought) {
      buttons[0]->setTexture((char*)"Textures/Menu/ShopMenu/Upgrade.png");
      buttons[0]->fill(0.8f, 0.0f, 0.0f);
    } else {
      buttons[0]->setTexture((char*)"Textures/Menu/ShopMenu/Buy.png");
      buttons[0]->fill(0.0f, 0.8f, 0.0f);

      lb.push_back(new Label);
      lb[1]->setup(x, y + 150, 30*ratioX, 30*ratioY);
      lb[1]->setWidth(250);
      lb[1]->setHeight(60);
        
      switch(shipType) {
        case GALACTICSHIP:
          break;
        case FIGHTERSHIP:
          lb[1]->setText((char*)"1000coins", 10);
          cost = 1000;
          break;
        case 3:
          lb[1]->setText((char*)"1500coins", 10);
          cost = 1500;
          break;
        case 4:
          lb[1]->setText((char*)"2000coins", 10);
          cost = 2000;
          break;
        case 5:
          lb[1]->setText((char*)"2500coins", 10);
          cost = 2500;
          break;
        case 6:
          lb[1]->setText((char*)"3000coins", 10);
          cost = 3000;
          break;
      }
      lb[1]->fill(0.6f, 0.6f, 0.6f);
      lb[1]->drawBorder(true);        
    }
  } else {
    bought = false;
    buttons[0]->setTexture((char*)"Textures/Menu/ShopMenu/Locked.png");
    buttons[0]->fill(0.6f, 0.6f, 0.6f);
    buttons[0]->disable();
  }  
  buttons[0]->drawBorder(true);
}

void Shipbox::draw() {  
  if(visible) {
    for(unsigned int i = 0; i < lb.size(); ++i)
      lb[i]->draw();
    for(unsigned int i = 0; i < buttons.size(); ++i)
      buttons[i]->draw();
    for(unsigned int i = 0; i < ship.size(); ++i)
      ship[i]->draw();      
  }  
}

void Shipbox::update(float mX, float mY, float deltaTime, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState) {
  if(!selected) {
    if(isMovingLeft) {
      x-=10*deltaTime;  
      if(x < (oldX-448)) {
        x = oldX - 453;
        isMovingLeft = false;
        oldX = x;
      }
      setX(); 
    }
  
    if(isMovingRight) {
      x+=10*deltaTime;
      if(x > (oldX+448)) {
        x = oldX + 453;
        isMovingRight = false;
        oldX = x;
      }
      setX();
    }
  
    if(x < 0 || x > 267+453*2.5) {
      visible = false;
    } else {
      visible = true;
    }  
   
    if(!checkIfMoving()) {
      for(unsigned int i = 0; i < buttons.size(); ++i)
        buttons[i]->update(mX, mY, mouseBtnState, prevMouseBtnState);
    }
  
    // Buy button clicked
    if(!bought && unlocked) {
      if(buttons[0]->Clicked()) {
        attemptBuy = true;
      }
    }
  } else {
  
  }
}

void Shipbox::buy() {
  bought = true;
  buttons[0]->setTexture((char*)"Textures/Menu/ShopMenu/Upgrade.png");
  buttons[0]->fill(0.8f, 0.0f, 0.0f);
  lb[1]->setVisible(false);
}

void Shipbox::setX() {
  for(unsigned int i = 0; i < lb.size(); ++i)
    lb[i]->setX(x);
  for(unsigned int i = 0; i < buttons.size(); ++i)
    buttons[i]->setX(x);
  for(unsigned int i = 0; i < ship.size(); ++i)
    ship[i]->setX(x);
}

void Shipbox::moveLeft() {
  isMovingLeft = true;
}

void Shipbox::moveRight() {
  isMovingRight = true;
}

