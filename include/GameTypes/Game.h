#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <sstream>

#include "../Ships/Ship.h"
#include "../Menus/Label.h"
#include "./DisplayManager.h"
#include "../Menus/PausedMenu.h"
#include "../Namespaces/Random.h"
#include "../Enemies/BasicEnemy.h"
#include "../Namespaces/Collisions.h"
#include "../Enemies/CorruptedStarShip.h"


class Game: public DisplayManager {
  public:
    Game();
    
    void draw();    
    void setup();
    void clean();
    void newWave();
    void restart();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);

  protected:
    void drawCrosshair();
    void drawBackground();
    
    bool isNew; //If Game is new
    bool paused;
    
    int score;
    int wave, level;
    
    // Cross Hair
    float lastChX, lastChY, ChX, ChY, ChRadius;
 
 
    Ship ship;
    Random boostRand;
    GLuint ChTexture; 
    PausedMenu pMenu;
    std::string strScore;
    Label lbWave, lbScore;
    std::vector<Enemy*> enemy;

};

#endif
