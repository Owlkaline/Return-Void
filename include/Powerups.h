#ifndef POWERUPS_H
#define POWERUPS_H

#ifdef __APPLE__
#include <OpenGL/gl.h>// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>// Header File For The GLu32 Library
#include <GLUT/glut.h>// Header File For The GLut Library
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

class Powerups
{
    public:
        Powerups();
        virtual ~Powerups();
        void setup();
        void draw();
        void Tick();
        void movement();

        bool getVisible();
        void setVisible(bool visible);

        float getX();
        float getY();
        float getWidth();
        float getHeight();

        void spawnMoney(float x, float y, GLuint texture);
        void spawnShield(float x, float y, GLuint texture);
        void spawnBomb(float x, float y, GLuint texture);
    protected:
        float x , y, width, height, speed;
        bool visible;
        GLuint texture;

        enum Type {
            Money,
            Shield,
            Bomb
        };
        Type type;
};

#endif // POWERUPS_H
