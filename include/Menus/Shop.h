#ifndef SHOP_H
#define SHOP_H

#include <sstream>

#include "../GameTypes/Menu.h"
#include "../Ships/Ship.h"

#include "./Shipbox.h"

#include "../Namespaces/Profile.h"

class Shop: public Menu {
  public:
    Shop();
    
    void setup();
    void restart();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);
    void drawBackground();
    void drawAfter();
    
    void save();
    
    void clean() {
      box.clear();
      box.erase(box.begin(), box.end());
      buttons.clear();
      buttons.erase(buttons.begin(), buttons.end());
      lb.clear();
      lb.erase(lb.begin(), lb.end());
      
    }
    
  protected:    
    Profile profile;
    
    std::vector<Ship*> ship;
    std::vector<Shipbox*> box;
    
    bool shipType[6];
    int numShips;
    int selected;
    int coins;
    int pos;
};

#endif
