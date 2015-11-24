#include "../include/Powerups.h"

Powerups::Powerups()
{
    //ctor
    width = 3;
    height = 4;
    speed = 0.25;
    visible = false;
}

Powerups::~Powerups()
{
    //dtor
}

void Powerups::spawnMoney(float x, float y, GLuint texture) {
    visible = true;
    type = Money;
    this->x = x;
    this->y = y;
    this->texture = texture;
}

void Powerups::spawnShield(float x, float y, GLuint texture) {
    visible = true;
    type = Shield;
    this->x = x;
    this->y = y;
    this->texture = texture;
}

void Powerups::spawnBomb(float x, float y, GLuint texture) {
    visible = true;
    type = Bomb;
    this->x = x;
    this->y = y;
    this->texture = texture;
}

void Powerups::movement() {
    y -= 0.65;
}

void Powerups::Tick() {
    movement();
}

void Powerups::draw() {

    glPushMatrix();
    glTranslatef(x, y, 0); // M1 - 2nd translation
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

void Powerups::setVisible(bool visible) { this->visible = visible; }

bool Powerups::getVisible() { return visible; }
float Powerups::getX() { return x; }
float Powerups::getY() { return y; }
float Powerups::getWidth() { return width; }
float Powerups::getHeight() { return height; }
