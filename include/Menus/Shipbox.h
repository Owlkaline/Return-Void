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
    void moveLeft();
    void moveRight();
    void draw();
    void update();
    void clean() { ship.clear();  ship.erase(ship.begin(), ship.end());
                   buttons.clear();  buttons.erase(buttons.begin(), buttons.end());
                   lb.clear();  lb.erase(lb.begin(), lb.end()); 
                 }
    bool checkIfMoving() { if(isMovingRight || isMovingLeft) { return true; } return false; }
  protected:
    void setX();
   
    float x, y, width, height;
    float oldX;
    bool unlocked, bought;
    bool isMovingLeft, isMovingRight;
    bool visible;
    std::vector<Ship*> ship;
    std::vector<Button*> buttons;
    std::vector<Label*> lb;
};

#endif
