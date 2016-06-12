#ifndef COLLISIONS_H
#define COLLISIONS_H

#define MAXLEVEL 1

#include <vector>

#include "../Ships/Ship.h"
#include "../Enemies/Enemy.h"

namespace Collisions{

    void drawQuadTree();
    void detect(Ship* ship, std::vector<Enemy*>);
    void drawHitBoxes(Ship* ship, std::vector<Enemy*> enemy);
    void drawBox(float x, float y, float width, float height);

    int getQuadrant(float x, float y, int level);
}

#endif

