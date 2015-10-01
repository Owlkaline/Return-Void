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

#include "Ship.h"
#include "Enemy.h"

#define BUTTON_UP   0
#define BUTTON_DOWN 1

double windowWidth = 100; //veiwing world x
double windowHeight = 100; // veiwing world y

double screenResX;
double screenResY;

int refreshMillis = 20;
double gridSquareWidth;

unsigned char keyState[255];
unsigned char prevKeyState[255];

GLuint Shiptexture;
GLuint Bullettexture;

Ship ship;
Enemy enemy;

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
   /*  case GLUT_KEY_F1:
         if (glutGameModeGet (GLUT_GAME_MODE_POSSIBLE)) {
             glutGameModeString("1920x1080:32");
             glutEnterGameMode();
         } 
         break;
     case GLUT_KEY_F2:
         glutLeaveGameMode();
         glutCreateWindow("Faggot window"); 
         glutFullScreen();
         break;*/
     }
}

void mouse(int button, int state, int x, int y) {
    
}

void collisions() {   
    if(enemy.getVisible()) {
        if( (ship.getX() >= enemy.getX() && ship.getX() <= ( enemy.getX() + enemy.getWidth() ) ) || 
          ((ship.getX() + ship.getWidth()) >= enemy.getX() && ( ship.getX() + enemy.getWidth() ) <= ( enemy.getX() + enemy.getWidth() )) ) {
               
           if( (ship.getY() >= enemy.getY() && ship.getY() <= ( enemy.getY() + enemy.getHeight() ) ) || 
              ((ship.getY() + ship.getHeight()) >= enemy.getY() && ( ship.getY() + enemy.getHeight() ) <= ( enemy.getY() + enemy.getHeight() )) ) {
                   
               enemy.looseHealth(10);
               ship.reset(); 
           }
        }
        for(int i = 0; i < 20; ++i) {
            if(ship.getBulletVisible(i)) {
                if( (ship.getBulletX(i) >= enemy.getX() && ship.getBulletX(i) <= ( enemy.getX() + enemy.getWidth() ) ) || 
                 ((ship.getBulletX(i) + ship.getBulletWidth(i)) >= enemy.getX() && ( ship.getBulletX(i) + enemy.getWidth() ) <= ( enemy.getX() + enemy.getWidth() )) ) {
               
                    if( (ship.getBulletY(i) >= enemy.getY() && ship.getBulletY(i) <= ( enemy.getY() + enemy.getHeight() ) ) || 
                      ((ship.getBulletY(i) + ship.getBulletHeight(i)) >= enemy.getY() && ( ship.getBulletY(i) + enemy.getHeight() ) <= ( enemy.getY() + enemy.getHeight() )) ) {
                       
                       ship.setBulletVisible(false, i);
                       enemy.looseHealth(1);
                    }
                } 
            }
        }
    }
}

void inGameKeyPress() {
    if(keyState[(unsigned char)'a'] == BUTTON_DOWN)
        ship.moveLeft();
    if(keyState[(unsigned char)'d'] == BUTTON_DOWN)
        ship.moveRight();
    if(keyState[(unsigned char)'w'] == BUTTON_DOWN)
        ship.moveUp();
    if(keyState[(unsigned char)'s'] == BUTTON_DOWN)
        ship.moveDown();
    if(keyState[32] == BUTTON_DOWN) {
        if(prevKeyState[32] != BUTTON_DOWN) {
                ship.fire();
        }
    }
    prevKeyState[32] = keyState[32];
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClear( GL_COLOR_BUFFER_BIT);
    ship.draw();
    
    if(enemy.getVisible())
        enemy.draw();
    if(keyState[27] == BUTTON_DOWN) {//ESC
        glutLeaveGameMode();
        exit(0);
    }
    inGameKeyPress();
    collisions();
        
    glFlush();       
    glutSwapBuffers(); 
}

GLuint LoadTexture( const char * filename )
{
  GLuint textures;
 
  int width, height;

  unsigned char * data;

  FILE * file;

  file = fopen( filename, "rb" );

  if ( file == NULL ) return 0;
 // printf("file opened\n");
  width = 2048;
  height = 2048;
  data = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );
  fclose( file );

  for(int i = 0; i < width * height ; ++i) {
      int index = i*3;
      unsigned char B,R;
      B = data[index];
      R = data[index+2];

      data[index] = R;
      data[index+2] = B;
   }
   
   glGenTextures(1, &textures);
   glBindTexture(GL_TEXTURE_2D, textures);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
   free( data );
   return textures;
    /*glGenTextures( 1, &textures );
    glBindTexture( GL_TEXTURE_2D, textures );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width,   height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
    //gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
    free( data );

    return textures;*/
}

void setup() {
    screenResX = glutGet(GLUT_SCREEN_WIDTH);
    screenResY = glutGet(GLUT_SCREEN_HEIGHT);

    printf("Screen Resolution: %f\n", screenResX);
    printf("Screen Resolution: %f\n", screenResY);

    Shiptexture = LoadTexture( "Textures/Ship.bmp" );
    Bullettexture = LoadTexture( "Textures/Bullet.bmp" );
    ship.setup(Shiptexture, Bullettexture);
    
    Shiptexture = LoadTexture( "Textures/Enemy.bmp" );
    Bullettexture = LoadTexture( "Textures/Bullet.bmp" );
    enemy.setup(Shiptexture, Bullettexture);
}

int main(int argc, char** argv) {
	/* initialize random seed: */
    srand (time(NULL));
    
    glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
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
    glEnable( GL_BLEND ); 
    glutIgnoreKeyRepeat(1);
    
    glutDisplayFunc(display);
    glutTimerFunc(0, Timer, 0);   
    glutKeyboardFunc(keyboard); 
    glutKeyboardUpFunc(keyboard_up); 
    glutSpecialFunc(specialKeys);
    
    //Ortho (x1,x2,y1,y2,z1,z2). 
    glOrtho(0.0, windowWidth, 0.0, windowHeight, -1.0, 1.0);   // setup a 100x100x2 viewing world
    //glOrtho(0.0, glutGet(GLUT_SCREEN_WIDTH)/100, 0.0, glutGet(GLUT_SCREEN_HEIGHT)/100, -1.0, 1.0);   // setup a wxhx2 viewing world
  //  glClearColor(0.0, 0.0, 0.0, 1.0);
    setup();
    printf("Setup Complete\n");
    glutMainLoop(); 
    return 0;
}
