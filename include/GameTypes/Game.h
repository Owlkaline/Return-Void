#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <sstream>

#include "./DisplayManager.h"
#include "../Ships/FighterShip.h"
#include "../Ships/GalacticShip.h"
#include "../Menus/Label.h"
#include "../Menus/PausedMenu.h"
#include "../Menus/HighscoreScreen.h"
#include "../Drops/Coins.h"
#include "../Drops/Health.h"
#include "../Drops/Shield.h"
#include "../Enemies/BasicEnemy.h" 
#include "../Enemies/HypnoEnemy.h" 
#include "../Enemies/CorruptedStarShip.h"
#include "../Namespaces/Random.h"
#include "../Namespaces/Collisions.h"


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
    bool inHighscore;
    
    int score;
    int coins;
    int wave, level;
    
    // Cross Hair
    float lastChX, lastChY, ChX, ChY, ChRadius;
 
    FighterShip ship;
    Random boostRand;
    GLuint ChTexture; 
    PausedMenu pMenu;
    std::string strScore;
    Label lbWave, lbScore, lbCoins;
    HighscoreScreen highscore;
    std::vector<Enemy*> enemy;
    std::vector<Drops*> powerups;
};

#endif
