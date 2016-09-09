#ifndef SHIPBOX_H
#define SHIPBOX_H

#include "../Ships/GalacticShip.h"
#include "../Ships/FighterShip.h"
#include "./Button.h"
#include "./Label.h"
#include "../Namespaces/Settings.h"

class Shipbox {
  public:
    ~Shipbox();
    
    void buy();
    void draw();
    void moveLeft();
    void moveRight();
    void setup(float x, float y, int shipType); 
    void setup(float x, float y, bool unlocked, bool bought, int shipType);   
    void update(float mX, float mY, float deltaTime, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState);

    bool AttemptBuy() { return attemptBuy; }
    bool checkIfMoving() { if(isMovingRight || isMovingLeft) { return true; } return false; }
    
    bool getBought() { return bought; }
    bool getUnlocked() { return unlocked; }
    bool getIsSelected() { return selected; }
    
    int getType() { return shipType; }
    int getCost() { attemptBuy = false; return cost; }    
    
    void clean() { 
      ship.clear();  
      ship.erase(ship.begin(), ship.end());
      buttons.clear();  
      buttons.erase(buttons.begin(), buttons.end());
      lb.clear();  
      lb.erase(lb.begin(), lb.end()); 
    }
    
    void setShip(int shipType) { 
      ship.clear(); 
      ship.erase(ship.begin(), ship.end());
      this->shipType = shipType;
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
          printf("Error in Shipbox.h: Unkown ship varient: %d", shipType);
          exit(0);
        break;
      }    
      for(unsigned int i = 0; i < ship.size(); ++i)
        ship[i]->VisualSetup(x, y);
    }
  protected:
    void setX();
    
    bool visible;
    bool selected;
    bool attemptBuy;
    bool unlocked, bought;
    bool isMovingLeft, isMovingRight;
    
    int cost;
    int shipType;
    
    float oldX;
    float x, y, width, height;
    
    std::vector<Label*> lb;
    std::vector<Ship*> ship;
    std::vector<Button*> buttons;  
};

#endif
