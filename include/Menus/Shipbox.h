#ifndef SHIPBOX_H
#define SHIPBOX_H

#include "../Ships/GalacticShip.h"
#include "../Ships/FighterShip.h"
#include "./Button.h"
#include "./Label.h"

class Shipbox {
  public:
    ~Shipbox();
    void setup(float x, float y, bool unlocked, bool bought, int shipType);
    void setup(float x, float y, int shipType);
    void moveLeft();
    void moveRight();
    void draw();
    void buy();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState);
    void clean() { ship.clear();  ship.erase(ship.begin(), ship.end());
                   buttons.clear();  buttons.erase(buttons.begin(), buttons.end());
                   lb.clear();  lb.erase(lb.begin(), lb.end()); 
                 }
    bool checkIfMoving() { if(isMovingRight || isMovingLeft) { return true; } return false; }
    bool getUnlocked() { return unlocked; }
    bool getBought() { return bought; }
    bool AttemptBuy() { return attemptBuy; }
    int getCost() { attemptBuy = false; return cost; }
    bool getIsSelected() { return selected; }
    int getType() { return shipType; }
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
    
    bool selected;
    int cost;
    int shipType;
    float x, y, width, height;
    float oldX;
    bool unlocked, bought;
    bool isMovingLeft, isMovingRight;
    bool visible;
    bool attemptBuy;
    std::vector<Ship*> ship;
    std::vector<Button*> buttons;
    std::vector<Label*> lb;
};

#endif
