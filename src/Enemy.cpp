#include "../include/Enemy.h"


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
}

void Enemy::setup(GLuint *EnemyText, float aspectRatio) {
    health = maxHealth;
    x = 0;
    y = boundryY - height;
    width = 5;
    height = 5;
    hitTimer = 0;
    isHit = false;
    visible = true;
    texture = EnemyText[0];
    this->aspectRatio = aspectRatio;
    bullets.setup(EnemyText[1], 0.5, 1, aspectRatio);
}

void Enemy::destroy() {
    //free(texture);
}

void Enemy::Tick(float Px, float Py, bool Pvisible) {
    moveDown();
    if(x < -width)
        x = boundryX;
    if(y < -height)
        visible = false;
    if(x > boundryX)
        x = -width;
   // if(y > boundryY )
    //    y = -height;

    if(Pvisible && !bullets.getVisible() && (rand() % (int)rate) < 10)
        fire(Px, Py);

}

void Enemy::draw() {
    glPushMatrix();
    //If enemy is hit alter colour to red, otherwise is normal colours
    if(isHit) {
        glColor3f(1.0f, 0.0f, 0.0f);
        hitTimer++;
        if(hitTimer > 3) {
            isHit = false;
            hitTimer = 0;
        }
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    glTranslatef(x, y, 0); // M1 - 2nd translation
    glScalef(1,aspectRatio,1);
    glRotatef(180, 0.0f, 0.0f, 1.0f); //M2
    glTranslatef( -x, -y, 0);  // M3 - 1st translation

    glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_POLYGON);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(x-width/2, y+height/2, 0.0);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(x+width/2, y+height/2, 0.0);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(x+width/2, y-height/2, 0.0);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(x-width/2, y-height/2, 0.0);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
}

void Enemy::drawBullets() {
    if(bullets.getVisible()) {
        //bullets.Tick(targetX, targetY);
       bullets.Tick();
    }
    bullets.draw();
}

void Enemy::fire(int Px, int Py) {
    targetX = Px;
    targetY = Py;
    bullets.fire(x + width/2, y, targetX, targetY, 0.75);
}

int Enemy::looseHealth(int LH) {
    health -= LH;
    if(health <= 0) {
        x = -1, y = -1;
        visible = false;
        return 100;
    }

    if(!isHit)
        isHit = true;
    return 0;
}

int Enemy::getHealth() { return health; }
float Enemy::getX() { return x; }
float Enemy::getY() { return y; }
int Enemy::getWidth() { return width; }
int Enemy::getHeight() { return height; }
bool Enemy::getVisible() { return visible; }

void Enemy::setX(float x) { this->x = x; }
void Enemy::setY(float y) { this->y = y; }
void Enemy::setSize(float multiple) { width = 5*multiple; height = 5*multiple; }
void Enemy::setMaxHealth(int maxHealth) { this->maxHealth = maxHealth; health = maxHealth;}
void Enemy::setSpeed(float speed) { this->speed = speed; }
void Enemy::setFireRate(float rate) { this->rate = 2500.f / rate; }
void Enemy::setVisible(bool visible) { this->visible = visible; }

bool Enemy::getBulletVisible() { return bullets.getVisible(); }
float Enemy::getBulletX() { return bullets.getX(); };
float Enemy::getBulletY() { return bullets.getY(); };
float Enemy::getBulletWidth() { return bullets.getWidth(); };
float Enemy::getBulletHeight() { return bullets.getHeight(); };

void Enemy::setBulletVisible(bool visible) { bullets.setVisible(visible); }

void Enemy::moveLeft() { x -= speed; }
void Enemy::moveRight() { x += speed; }
void Enemy::moveUp() { y += speed; }
void Enemy::moveDown() { y -= speed; }
