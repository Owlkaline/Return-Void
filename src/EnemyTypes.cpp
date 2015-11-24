#include "../include/EnemyTypes.h"

void BasicEnemy::setup(GLuint *enemyTextures, GLuint *enemyBulletTextures,  float aspectRatio) {
    maxHealth = 8;
    health = maxHealth;
    x = -100;
    y = -100;
    width = 3;
    height = 5;
    hitTimer = 0;
    isHit = false;
    visible = true;
    speed = 0.3f;
    fireRate = 30;
    texture = enemyTextures[1];
    this->aspectRatio = aspectRatio;
    bullets.setup(enemyBulletTextures[0], 0.5, 0.5, aspectRatio);
    score = 300;
}

void BasicEnemy::spawn(float x, float y, float speed, float fireRate) {
    this->x = x;
    this->y = y;
    this->speed = speed;
    setMaxHealth(maxHealth);
    this->fireRate = fireRate;
    setSize(5);
    visible = true;
}
