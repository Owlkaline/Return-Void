#include "Enemy.h"

#include <stdlib.h>

Enemy::Enemy() {
        width = 6;
        height = 10;         
        health = 10; 
        boundryX = 100;
        boundryY = 92 - height;
        x = 0;
        y = boundryY - height; 
        isVisible = true;
        printf("Enemy Constructed\n");
   }
   
void Enemy::setup(GLuint EnemyText, GLuint bulletText) {
    health = 10; 
    x = 0;
    y = boundryY - height; 
    isVisible = true;
    texture = EnemyText; 
    bullets.setup(bulletText);
}

void Enemy::destroy() {
    //free(texture);
}

void Enemy::draw() {
    //glColor3f(0.0, 1.0, 0.0);
    moveRight();
    if(x < -width)
        x = boundryX;
    if(y < -height)
        y = boundryY;
    if(x > boundryX)
        x = -width;
    if(y > boundryY )
        y = -height;

    glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);
    
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(x, y + height, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x + width, y + height, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x + width, y, 0.0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x, y, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
 
    if(bullets.getVisible())
        bullets.draw();
    
    
}

void Enemy::fire() {
    bullets.fire(x + width/2 - 0.5, y + height, 0.75);
}  

int Enemy::looseHealth(int LH) { health -= LH; if(health <= 0) { health = 10; x = 0, y = boundryY - height; return 103;} return 0;};     
int Enemy::getHealth() { return health; }
float Enemy::getX() { return x; }
float Enemy::getY() { return y; }
int Enemy::getWidth() { return width; }
int Enemy::getHeight() { return height; }
void Enemy::setVisible(bool visible) { isVisible = visible; }
bool Enemy::getVisible() { return isVisible; }
void Enemy::setBulletVisible(bool visible) { bullets.setVisible(false); }
void Enemy::moveLeft() { x -= 0.3f; }
void Enemy::moveRight() { x += 0.3f; }
void Enemy::moveUp() { y += 0.3f; }
void Enemy::moveDown() { y -= 0.3f; }
