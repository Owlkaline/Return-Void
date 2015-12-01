#ifndef ENEMYTYPES_H
#define ENEMYTYPES_H

#include "BaseEnemy.h"

class BasicEnemy: public BaseEnemy {
    public:
        virtual void setup(GLuint *enemyTextures, GLuint *enemyBulletTextures,  float aspectRatio);
        virtual void spawn(float x, float y, float speed, float fireRate);
};


#endif
