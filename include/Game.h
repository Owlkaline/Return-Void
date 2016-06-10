#ifndef GAME_H
#define GAME_H

#include <vector>

#include "./DisplayManager.h"
#include "./Ship.h"
#include "./BasicEnemy.h"
#include "./LoadTexture.h"
#include "./Collisions.h"

class Game: public DisplayManager {
  public:
    Game();
    
    void draw();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);
    void setup();
    void restart();
    void clean();
    
    void newWave();
  protected:
    void drawBackground();
    void drawCrosshair();
    Ship ship;
    std::vector<Enemy*> enemy;
    bool isNew;
    // Cross Hair
    float lastChX, lastChY, ChX, ChY, ChRadius;
    GLuint ChTexture;
};

#endif
