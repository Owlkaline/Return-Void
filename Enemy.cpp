#include "Enemy.h"


Enemy::Enemy() {
    srand (time(NULL));
    width = 5;
    height = 5;  
    speed = 0.3f;
    maxHealth = 5;       
    health = maxHealth; 
    boundryX = 100;
    boundryY = 92 - height;
    rate = 2500.0f;
    x = 0;
    y = boundryY - height; 
    visible = true;
    printf("Enemy Constructed\n");
}
   
void Enemy::setup(GLuint *EnemyText) {
    health = maxHealth; 
    x = 0;
    y = boundryY - height; 
    visible = true;
    texture = EnemyText[0]; 
    bullets.setup(EnemyText[1], 0.5, 1);
}

void Enemy::destroy() {
    //free(texture);
}

void Enemy::Tick(float Px, float Py) {
    moveDown();
    if(x < -width)
        x = boundryX;
    if(y < -height)
        visible = false;
    if(x > boundryX)
        x = -width;
   // if(y > boundryY )
    //    y = -height;
    
    if(!bullets.getVisible() && (random() % (int)rate) < 10)
        fire(Px, Py);
}

void Enemy::draw() {

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
}

void Enemy::drawBullets() {
    if(bullets.getVisible()) {
        bullets.Tick(targetX, targetY);
    }
    bullets.draw();
}

void Enemy::fire(int Px, int Py) {
    targetX = Px;
    targetY = Py;
    bullets.fire(x + width/2, y, -0.75, targetX, targetY);
}  

int Enemy::looseHealth(int LH) { health -= LH; if(health <= 0) { x = -1, y = -1; visible = false; return 100;} return 0;};     
int Enemy::getHealth() { return health; }
float Enemy::getX() { return x; } 
float Enemy::getY() { return y; }
int Enemy::getWidth() { return width; }
int Enemy::getHeight() { return height; }
bool Enemy::getVisible() { return visible; }

void Enemy::setX(float X) { x = X; }
void Enemy::setY(float Y) { y = Y; }
void Enemy::setSize(float multiple) { width *= multiple; height *= multiple; }
void Enemy::setMaxHealth(int mHealth) { maxHealth = mHealth; health = maxHealth;}
void Enemy::setSpeed(float mSpeed) { speed = mSpeed; }
void Enemy::setFireRate(float Rate) { rate = 2500.f / Rate; }
void Enemy::setVisible(bool Visible) { visible = Visible; }

bool Enemy::getBulletVisible() { return bullets.getVisible(); }
float Enemy::getBulletX() { return bullets.getX(); }; 
float Enemy::getBulletY() { return bullets.getY(); }; 
float Enemy::getBulletWidth() { return bullets.getWidth(); }; 
float Enemy::getBulletHeight() { return bullets.getHeight(); }; 

void Enemy::setBulletVisible(bool visible) { bullets.setVisible(false); }

void Enemy::moveLeft() { x -= speed; }
void Enemy::moveRight() { x += speed; }
void Enemy::moveUp() { y += speed; }
void Enemy::moveDown() { y -= speed; }
