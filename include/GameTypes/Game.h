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
#include "../Menus/FloatingText.h"
#include "../Menus/HighscoreScreen.h"

#include "../Drops/Coins.h"
#include "../Drops/Health.h"
#include "../Drops/Shield.h"

#include "../Enemies/AlphaOne.h"
#include "../Enemies/BasicEnemy.h" 
#include "../Enemies/HypnoEnemy.h" 
#include "../Enemies/CorruptedStarShip.h"

#include "../Namespaces/Random.h"
#include "../Namespaces/Profile.h"
#include "../Namespaces/Settings.h"
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
    int selected;
    
    float offsetY;
    // Cross Hair
    float lastChX, lastChY, ChX, ChY, ChRadius; 
 
    Profile profile;
    Random boostRand;     
    PausedMenu pMenu;
    Settings settings;
    std::string strScore;
    HighscoreScreen highscore;
    GLuint ChTexture, background;    
    Label lbWave, lbWaveStatic, lbScore, lbCoins;    
    
    std::vector<Ship*> ship;
    std::vector<Enemy*> enemy;
    std::vector<Drops*> powerups;
    std::vector<FloatingText*> Ftext;
};

#endif
