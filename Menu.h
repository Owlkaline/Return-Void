#ifndef MENU_H
#define MENU_H

#ifdef __APPLE__
#include <OpenGL/gl.h>// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>// Header File For The GLu32 Library
#include <GLUT/glut.h>// Header File For The GLut Library
#else
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <png.h>
#endif

#include <stdio.h> 
#include <cstdlib>
#include <stdlib.h>
#include <fstream>

#define BUTTON_UP   0
#define BUTTON_DOWN 1

class Menu 
{
    public:
        Menu();
        void setup();
        void saveSettings();
        void readSettings();
        void changeMenu(int a); 
        int keyPress(unsigned char* keyState, unsigned char* prevKeyState);
        void draw();       
    protected:  
        void drawChar(int PosX, int PosY, float R, float G, float B, char str[25], int length);
        int select;
        int height;
        int width;        
        int numOptions;
        bool showHitBox;
        void drawBackground();
        void drawRectangle(float x, float y, int textnum);
        int screen;
        GLuint LoadTexture( const char * filename );
        GLuint texture;
        GLuint textures[8];
};


#endif
