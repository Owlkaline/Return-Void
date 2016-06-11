#ifndef COLLISIONS_H
#define COLLISIONS_H

#define MAXLEVEL 1

#include <vector>

#include "./Enemy.h"
#include "./Ship.h"


namespace Collisions{
    
    void detect(Ship* ship, std::vector<Enemy*>);

    int getQuadrant(float x, float y, int level);
}

#endif

