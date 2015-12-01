#include "../include/BaseEnemy.h"

BaseEnemy::BaseEnemy() {
    srand (time(NULL));
    boundryX = 100;
    boundryY = 92 - height;
}

void BaseEnemy::setup(GLuint *enemyTextures, GLuint *enemyBulletTextures,  float aspectRatio) {
    maxHealth = 5;
    health = maxHealth;
    x = -100;
    y = -100;
    width = 3;
    height = 5;
    hitTimer = 0;
    isHit = false;
    visible = true;
    speed = 0.3f;
    fireRate = 300;
    texture = enemyTextures[0];
    this->aspectRatio = aspectRatio;
    bullets.setup(enemyBulletTextures[0], 0.5, 0.5, aspectRatio);
    score = 100;
}

void BaseEnemy::destroy() {
    //free(texture);
}

void BaseEnemy::movement() {
    moveDown();
}

void BaseEnemy::Tick(float Px, float Py, bool Pvisible) {
    movement();
    if(x < -width)
        x = boundryX;
    if(y < -height)
        visible = false;
    if(x > boundryX)
        x = -width;

    if(Pvisible && !bullets.getVisible() && shootTimer > fireRate) {
        shootTimer = 0;
        fire(Px, Py);
    }
    shootTimer++;
}

void BaseEnemy::spawn(float x, float y, float speed, int maxHealth, float fireRate) {
    this->x = x;
    this->y = y;
    this->speed = speed;
    setMaxHealth(maxHealth);
    this->fireRate = fireRate;
    setSize(5);
    visible = true;
}

void BaseEnemy::draw() {
    glPushMatrix();
    //If EnemyBase is hit alter colour to red, otherwise is normal colours
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

void BaseEnemy::drawBullets() {
    if(bullets.getVisible()) {
       bullets.Tick();
    }
    bullets.draw();
}

void BaseEnemy::fire(int Px, int Py) {
    targetX = Px;
    targetY = Py;
    bullets.fire(x + width/2, y, targetX, targetY, 0.75);
}

int BaseEnemy::Drops() {
    int random = rand()%100;
    if(random < 75) {
        random = rand()%90;
        if(random < 30) {
            item = Money;
        } else if (random > 60) {
            item = Shield;
        } else {
            item = Bomb;
        }
        return item;
    }
    return -1;
}

int BaseEnemy::looseHealth(int LH) {
    health -= LH;
    if(health <= 0) {
        visible = false;
        return score;
    }

    if(!isHit)
        isHit = true;
    return 0;
}

int BaseEnemy::getHealth() { return health; }
float BaseEnemy::getX() { return x; }
float BaseEnemy::getY() { return y; }
float BaseEnemy::getWidth() { return width; }
float BaseEnemy::getHeight() { return height; }
bool BaseEnemy::getVisible() { return visible; }

void BaseEnemy::setX(float x) { this->x = x; }
void BaseEnemy::setY(float y) { this->y = y; }
void BaseEnemy::setSize(float size) { width = size; height = size; }
void BaseEnemy::setSize(float width, float height) { this->width = width; this->height = height; }
void BaseEnemy::setMaxHealth(int maxHealth) { this->maxHealth = maxHealth; health = maxHealth;}
void BaseEnemy::setSpeed(float speed) { this->speed = speed; }
void BaseEnemy::setFireRate(float fireRate) { this->fireRate = fireRate; }
void BaseEnemy::setVisible(bool visible) { this->visible = visible; }

bool BaseEnemy::getBulletVisible() { return bullets.getVisible(); }
float BaseEnemy::getBulletX() { return bullets.getX(); };
float BaseEnemy::getBulletY() { return bullets.getY(); };
float BaseEnemy::getBulletWidth() { return bullets.getWidth(); };
float BaseEnemy::getBulletHeight() { return bullets.getHeight(); };

void BaseEnemy::setBulletVisible(bool visible) { bullets.setVisible(visible); }

void BaseEnemy::moveLeft() { x -= speed; }
void BaseEnemy::moveRight() { x += speed; }
void BaseEnemy::moveUp() { y += speed; }
void BaseEnemy::moveDown() { y -= speed; }

