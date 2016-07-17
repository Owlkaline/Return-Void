#ifndef SHOP_H
#define SHOP_H

#include "../GameTypes/Menu.h"

#include "./Shipbox.h"

#include "../Ships/FighterShip.h"
#include "../Ships/GalacticShip.h"

#include "../Namespaces/Profile.h"

class Shop: public Menu {
  public:
    Shop();
    
    void setup();
    void restart();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);
    void drawBackground();
    void drawAfter();
    
    void clean() {
      box.clear();
      box.erase(box.begin(), box.end());
    }
    
  protected:
    void drawBox(float x, float y, float width, float height);
    
    Profile profile;
    FighterShip FShip;
    GalacticShip GShip;
    
    std::vector<Shipbox*> box;
    
    int pos;
};

#endif
