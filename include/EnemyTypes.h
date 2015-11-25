#ifndef ENEMYTYPES_H
#define ENEMYTYPES_H

#include "EnemyBase.h"

class BasicEnemy: public EnemyBase {
    public:
        virtual void setup(GLuint *enemyTextures, GLuint *enemyBulletTextures,  float aspectRatio);
        virtual void spawn(float x, float y, float speed, float fireRate);
};


#endif
