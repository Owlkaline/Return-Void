#include "../include/EnemyBase.h"

EnemyBase::EnemyBase() {
    srand (time(NULL));
    boundryX = 100;
    boundryY = 92 - height;
}

void EnemyBase::setup(GLuint *enemyTextures, GLuint *enemyBulletTextures,  float aspectRatio) {
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

void EnemyBase::destroy() {
    //free(texture);
}

void EnemyBase::movement() {
    moveDown();
}

void EnemyBase::Tick(float Px, float Py, bool Pvisible) {
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

void EnemyBase::spawn(float x, float y, float speed, int maxHealth, float fireRate) {
    this->x = x;
    this->y = y;
    this->speed = speed;
    setMaxHealth(maxHealth);
    this->fireRate = fireRate;
    setSize(5);
    visible = true;
}

void EnemyBase::draw() {
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

void EnemyBase::drawBullets() {
    if(bullets.getVisible()) {
       bullets.Tick();
    }
    bullets.draw();
}

void EnemyBase::fire(int Px, int Py) {
    targetX = Px;
    targetY = Py;
    bullets.fire(x + width/2, y, targetX, targetY, 0.75);
}

int EnemyBase::Drops() {
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

int EnemyBase::looseHealth(int LH) {
    health -= LH;
    if(health <= 0) {
        visible = false;
        return score;
    }

    if(!isHit)
        isHit = true;
    return 0;
}

int EnemyBase::getHealth() { return health; }
float EnemyBase::getX() { return x; }
float EnemyBase::getY() { return y; }
float EnemyBase::getWidth() { return width; }
float EnemyBase::getHeight() { return height; }
bool EnemyBase::getVisible() { return visible; }

void EnemyBase::setX(float x) { this->x = x; }
void EnemyBase::setY(float y) { this->y = y; }
void EnemyBase::setSize(float size) { width = size; height = size; }
void EnemyBase::setSize(float width, float height) { this->width = width; this->height = height; }
void EnemyBase::setMaxHealth(int maxHealth) { this->maxHealth = maxHealth; health = maxHealth;}
void EnemyBase::setSpeed(float speed) { this->speed = speed; }
void EnemyBase::setFireRate(float fireRate) { this->fireRate = fireRate; }
void EnemyBase::setVisible(bool visible) { this->visible = visible; }

bool EnemyBase::getBulletVisible() { return bullets.getVisible(); }
float EnemyBase::getBulletX() { return bullets.getX(); };
float EnemyBase::getBulletY() { return bullets.getY(); };
float EnemyBase::getBulletWidth() { return bullets.getWidth(); };
float EnemyBase::getBulletHeight() { return bullets.getHeight(); };

void EnemyBase::setBulletVisible(bool visible) { bullets.setVisible(visible); }

void EnemyBase::moveLeft() { x -= speed; }
void EnemyBase::moveRight() { x += speed; }
void EnemyBase::moveUp() { y += speed; }
void EnemyBase::moveDown() { y -= speed; }

