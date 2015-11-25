#include "../include/Player.h"

#include <stdlib.h>

Player::Player() {
    boundryX = 100;
    boundryY = 92;
    printf("Player Constructed\n");
}

void Player::setup(GLuint *newTextures, float newAspectRatio) {
    x = 50.0f;
    y = 50.0f;
    angle = 0;
    speed = 0.5f;
    aspectRatio = newAspectRatio;
    width = 5;
    height=5;
    health = 5;
    drawInvincible = true;
    fireRate = 2000;
    invincible = false;
    alive = true;
    visible = true;
    PlayerText = newTextures[0];
    PlayerLeftText = newTextures[1];
    PlayerRightText = newTextures[2];
    texture = newTextures[0];

    bulletTexture = newTextures[3];
    invincTimer = 0;
    flashTimer = 0;

    for(unsigned int i = 0; i < bullets.size(); i++) {
        bullets[i]->setup(bulletTexture, 0.5, 3, aspectRatio);
    }
    printf("Player bullets constructed\n");
}

void Player::destroy() {
    for(unsigned int i = 0; i < bullets.size(); i++) {
        bullets.erase(bullets.begin() + i);
    }
    //free(PlayerText);
   // free(PlayerLeftText);
   // free(PlayerRightText);
   // free(texture);
}

void Player::leftImage() {
    texture = PlayerLeftText;
}

void Player::rightImage() {
    texture = PlayerRightText;
}

void Player::stationaryImage() {
    texture = PlayerText;
}

void Player::Tick(float mouseX, float mouseY) {

    if(health < 0) {
        health = 0;
        alive = false;
        visible = false;
    }
    lastMouseX = mouseX;
    lastMouseY = mouseY;
    float diffx = mouseX - x;
    float diffy = mouseY - y;
    diffy /= aspectRatio;
    float distance = pow(pow(diffy,2.0f) + pow(diffx,2.0f), 0.5f);
    directionX = (diffx) / (distance);
    directionY = (diffy*aspectRatio) / (distance);

     if (diffx > 0.0 && diffy > 0.0) {//Quadrant 1
        angle = (float)atan(diffy/diffx) *180.0f / (float)M_PI ;
        angle = angle - 90.0f;
    }else if(diffx < 0 && diffy > 0) {//Quadrant 2
        angle = (float)atan(diffy/diffx) *180.0f / (float)M_PI ;
        angle = angle + 90.0f;
    } else     if(diffx < 0 && diffy < 0) {//Quadrant 3
        angle = (float)atan(diffy/diffx) *180.0f / (float)M_PI ;
        angle = angle+90.0f;
    } else     if(diffx > 0 && diffy < 0) {//Quadrant 4
        angle = (float)atan(diffy/diffx) * 180.0f / (float)M_PI ;
        angle = angle - 90.0f;
    }

    for(unsigned int i = 0; i < bullets.size(); ++i) {
        if(bullets[i]->getVisible()) {
            bullets[i]->Tick();
        } else {
            bullets.erase(bullets.begin() + i);
        }
    }
    invincTimer++;
    flashTimer++;
}

void Player::drawShip() {
    glPushMatrix();

    glTranslatef(x, y, 0); // M1 - 2nd translation
    glScalef(1,aspectRatio,1);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);                  // M2
        //glScalef(1,aspectRatio,1);
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
}

void Player::flash() {
    if(invincTimer > 80)
        invincible = false;

    if(flashTimer > 10) {
        glColor3f(0.2f, 0.2f, 0.5f);
        drawShip();
    } else {
        glColor3f(1.0, 1.0, 1.0);
        drawShip();
    }

    if(flashTimer > 20)
        flashTimer = 0;
}

void Player::draw() {
    if(!visible)
        return;

    for(unsigned int i = 0; i < bullets.size(); ++i) {
        if(bullets[i]->getVisible())
            bullets[i]->draw();
    }

    //glColor3f(0.0, 1.0, 0.0);
    if(x < 0+width/2)
        x = width/2;
    if(y < 0+height/2)
        y = height/2;
    if(x > boundryX - width/2)
        x = boundryX - width/2;
    if(y > boundryY - height/2)
        y = boundryY - height/2;

    if(invincible) {
        flash();
    } else {
        drawShip();
    }
}

void Player::fire() {
    bullets.push_back(new Bullet);
    int i = bullets.size()-1;
    bullets[i]->setup(bulletTexture, 0.25, 1.5, aspectRatio);
    bullets[i]->fire( x, y, directionX, directionY, 1.0, angle);
}

int Player::getBulletNum() { return bullets.size(); }

void Player::moveLeft() { x -= speed; }
void Player::moveRight() { x += speed; }
void Player::moveUp() { y += speed; }
void Player::moveDown() { y -= speed; }

void Player::rotateRight() { angle--; }
void Player::rotateLeft() { angle++; }
void Player::setHealth(int health) { this->health = health; }
void Player::setVisible(bool visible) { this->visible = visible; }
float Player::getWidth() { return width; }
int Player::getHealth() { return health; }
float Player::getHeight() { return height*aspectRatio; }
float Player::getX() { return x; }
float Player::getY() { return y; }
bool Player::isAlive() { return alive; }
bool Player::getVisible() { return visible; }
bool Player::getInvincible() { return invincible; }

void Player::takeHealth() { health -= 1; if(health < 0) health = 0; }
void Player::setBulletVisible(bool visible, int i) { bullets[i]->setVisible(visible); }
bool Player::getBulletVisible(int i) { return bullets[i]->getVisible(); }
float Player::getBulletX(int i) { return bullets[i]->getX(); }
float Player::getBulletY(int i) { return bullets[i]->getY(); }
int Player::getBulletWidth(int i) { return bullets[i]->getWidth(); }
int Player::getBulletHeight(int i) { return bullets[i]->getHeight(); }

void Player::respawn(int x, int y) { invincible = true; invincTimer = 0; flashTimer = 0; this->x = x; this->y = y; visible = true;}

