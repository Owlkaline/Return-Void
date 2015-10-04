#ifdef __APPLE__
#include <OpenGL/gl.h>// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>// Header File For The GLu32 Library
#include <GLUT/glut.h>// Header File For The GLut Library
#else
#include <GL/glut.h>
#include <GL/freeglut.h>
#endif

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>      /* time */
#include <ctype.h>

#include "Game.h"
#include "Menu.h"

#define BUTTON_UP   0
#define BUTTON_DOWN 1

enum Screen {
    sMenu = 0,
    sGame = 1,
    sOptions = 2  
};

double windowWidth = 100; //veiwing world x
double windowHeight = 100; // veiwing world y

double screenResX;
double screenResY;

int refreshMillis = 20;
double gridSquareWidth;

unsigned char keyState[255];
unsigned char prevKeyState[255];

Game game;
Menu menu;
Screen screen;

void Timer(int value) {
   glutPostRedisplay();    // Post a paint request to activate display()
   glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}

void keyboard(unsigned char key, int x, int y) {
        keyState[putchar (tolower(key))] = BUTTON_DOWN;
}

void keyboard_up(unsigned char key, int x, int y) {
        keyState[putchar (tolower(key))] = BUTTON_UP;        
}

void specialKeys(int key, int x, int y) {
     switch (key) { 
     case GLUT_KEY_LEFT:
            break; 
     }
}

void mouse(int button, int state, int x, int y) {
    
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    
    switch(screen) {
       case sGame:
           if(keyState[27] == BUTTON_DOWN) //ESC
               screen = sMenu;
               
           game.keyPress(keyState, prevKeyState);
           game.draw();
           break;
       case sMenu:           
           int screenNum;
           screenNum = menu.keyPress(keyState, prevKeyState);
           if(keyState[27] == BUTTON_DOWN) {//ESC
               if(prevKeyState[27] != BUTTON_DOWN) {
                   glutLeaveGameMode();
                   exit(0);
               }
           }
           
           switch(screenNum) {
               case -1:
                   exit(0);                  
                   break;
               case 1: 
                   screen = sGame;
                  // game.setup();
                   break;
               case 2:
                   screen = sOptions;
                   break;
              
           }
           menu.draw();
           break;
       case sOptions:
           if(keyState[27] == BUTTON_DOWN) {//ESC
               screen = sMenu;
           }
           break;
    }
    keyState[27] = prevKeyState[27];
    
        
    glFlush();       
    glutSwapBuffers(); 
}

GLuint LoadTexture( const char * filename ) {
    GLuint textures;
 
    int width, height;

    unsigned char * data;

    FILE * file;

    file = fopen( filename, "rb" );
  
    if ( file == NULL ) return 0;
    // printf("file opened\n");
    width = 2048;
    height = 2048;
    data = (unsigned char *)malloc( width * height * 4 );
    //int size = fseek(file,);
    fread( data, width * height * 4, 1, file );
    fclose( file );
 
    unsigned char t, t1, t2, t3;
    for(int j = 0; j < height; ++j){
        for(int i = 0; i < width; ++i) {
            //A, B, G, R
            t=data[i]; //A
            t1=data[i+1];//B
            t2=data[i+2];//G
            t3=data[i+3];//R
            //R, G, B, A
            data[j]=t2;
            data[j+1]=t1;
            data[j+2]=t;
            data[j+3]=t3;

            i+=4;
            j+=4;
        }  
     }
     glGenTextures(1, &textures);
     glBindTexture(GL_TEXTURE_2D, textures);
  
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
     free( data );
     return textures;
}

void setup() {
    screenResX = glutGet(GLUT_SCREEN_WIDTH);
    screenResY = glutGet(GLUT_SCREEN_HEIGHT);

    printf("Screen Resolution: %f\n", screenResX);
    printf("Screen Resolution: %f\n", screenResY);
    
    screen = sMenu;
    GLuint textures[12];
    textures[0] = LoadTexture( "Textures/Game/Ship.bmp" );
    textures[1] = LoadTexture( "Textures/Game/ShipTiltLeft.bmp" );
    textures[2] = LoadTexture( "Textures/Game/ShipTiltRight.bmp" );
    textures[3] = LoadTexture( "Textures/Game/Bullet.bmp" );    
    textures[4] = LoadTexture( "Textures/Game/Enemy.bmp" );    
    textures[5] = LoadTexture( "Textures/Game/Bullet.bmp" );
    textures[6] = LoadTexture( "Textures/Menu/Start.bmp" );
    textures[7] = LoadTexture( "Textures/Menu/Options.bmp" );
    textures[8] = LoadTexture( "Textures/Menu/Exit.bmp" );
    textures[9] = LoadTexture( "Textures/Menu/SelectedStart.bmp" );
    textures[10] = LoadTexture( "Textures/Menu/SelectedOptions.bmp" );
    textures[11] = LoadTexture( "Textures/Menu/SelectedExit.bmp" );
    menu.setup(textures);
    game.setup(textures); 

}

int main(int argc, char** argv) {
	/* initialize random seed: */
    srand (time(NULL));
    
    glClearColor(255.0, 0.0, 255.0, 0.0);         // black background
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    char mode_string[24];
 
    sprintf(mode_string, "%dx%d:32@60", glutGet(GLUT_SCREEN_WIDTH),
    glutGet(GLUT_SCREEN_HEIGHT));
    glutGameModeString(mode_string);
    if(glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
        printf("GameMode %s is possible\n", mode_string);
                                 // destroys the current graphics window
        glutDestroyWindow(0);
        glutEnterGameMode();
                                 // hide the cursor
        glutSetCursor(GLUT_CURSOR_NONE);
    } else {
        printf("GameMode %s NOT possible\n", mode_string);
        glutFullScreen();
    }
    glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //  glEnable( GL_BLEND ); 
    glutIgnoreKeyRepeat(1);
    
    glutDisplayFunc(display);
    glutTimerFunc(0, Timer, 0);   
    glutKeyboardFunc(keyboard); 
    glutKeyboardUpFunc(keyboard_up); 
    glutSpecialFunc(specialKeys);
    
    //Ortho (x1,x2,y1,y2,z1,z2). 
    //glOrtho(0.0, glutGet(GLUT_SCREEN_WIDTH)/100, 0.0, glutGet(GLUT_SCREEN_HEIGHT)/100, -1.0, 1.0); setup a wxhx2 viewing world
    glOrtho(0.0, windowWidth, 0.0, windowHeight, -1.0, 1.0);   // setup a 100x100x2 viewing world
    glClearColor(0.0, 0.0, 0.0, 1.0);
    setup();
    printf("Setup Complete\n");
    glutMainLoop(); 
    return 0;
}
