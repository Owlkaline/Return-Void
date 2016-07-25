//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>// Header File For The GLu32 Library
#else
#include <GL/glu.h>
#include <png.h>
#endif

#include <stdio.h>

#include "../include/Menus/Shop.h"
#include "../include/Menus/MainMenu.h"
#include "../include/Menus/SettingsMenu.h"
#include "../include/Menus/HighscoreScreen.h"

#include "../include/GameTypes/Game.h"
#include "../include/GameTypes/Menu.h"

#include "../include/Namespaces/Settings.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int screenResX;
int screenResY;

int type = MAINMENU;

int refreshMillis = 20;

//Screen grid 100x100
double gridWidth = 100; //veiwing world x
double gridHeight = 100; // veiwing world y

//Aspect ratio of screen resolution
float aspectRatio;

//Scaled aspect Ratios, for the width and height
float aspectW;
float aspectH;

//Current coords of the mouse
int mouseX, mouseY;

//Settings settings;
Settings settings;

//Keeps the current key state, keeps the key state of the previous key state
unsigned int  specialKey[5];
unsigned int  mouseBtnState[3];
unsigned int  prevSpeicalKey[5];
unsigned int  prevMouseBtnState[3];

unsigned char keyState[255];
unsigned char prevKeyState[255];

GLuint mouseTexture;

SDL_Surface* surface;
TTF_Font* font;

DisplayManager* Display[5] = { new MainMenu(), new Game(), new SettingsMenu(), new Shop(), new HighscoreScreen() };

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Render flag
bool gRenderQuad = true;

void mouse() {
  int x, y;
  SDL_GetMouseState( &x, &y );
  mouseY = (screenResY - y) * aspectH;
  mouseX = x*aspectW;
}

//Updates what keys are pressed
void keyboard(unsigned char key) {
  keyState[putchar (tolower(key))] = BUTTON_DOWN;
}

//Updates what keys are released
void keyboard_up(unsigned char key) {
    keyState[putchar (tolower(key))] = BUTTON_UP;
}

void mouseBtn(int btn, int state) {  
/* if(state == BUTTON_DOWN) {
    state = BUTTON_UP;
  } else {
    state = BUTTON_DOWN;
  }*/
  
  if(btn == SDL_BUTTON_LEFT) {
    btn = 0;
  } else if(btn == SDL_BUTTON_RIGHT) {
    btn = 1;
  } else {
    btn = 2;
  }
  
  mouseBtnState[btn] = state;
}
  

void drawCursor() {
  if(type != GAME) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mouseTexture);
    // Nice blue #1e00d5
    glColor3f(0.117647059f, 0, 0.835294197f);

    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(mouseX-20, mouseY+20, 0.0);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(mouseX+20, mouseY+20, 0.0);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(mouseX+20, mouseY-20, 0.0);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(mouseX-20, mouseY-20, 0.0);
    glEnd();

    glColor3f(1.0, 1.0, 1.0f);
    glDisable(GL_TEXTURE_2D);
  }
}

void clean() {
	//Destroy window	
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void display() {      
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wipes screen clear

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//Blends colours with alpha
  glClearColor(0.0f, 0.0f, 0.0f, 255.0f);
  
  //Texture options
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glColor4ub(255,255,255,255); //sets full colours and alpha
  surface  = SDL_GetWindowSurface(gWindow);
    SDL_Color White = {0, 255, 0,255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "Testing text", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
  SDL_Rect pos;
  pos.x = SPACE_X_RESOLUTION/2;
  pos.y = SPACE_Y_RESOLUTION/2;
  pos.w = 100;
  pos.h = 100;
  SDL_BlitSurface(surfaceMessage, NULL, surface, &pos);

  Display[type]->update(mouseX, mouseY, mouseBtnState, prevMouseBtnState, keyState, prevKeyState);
  Display[type]->draw();
  
  drawCursor();
  
  if(Display[type]->hasEnded()) {
    int newtype = Display[type]->getEndType();
    switch(newtype) {
      case EXIT:
        clean();
        exit(0);
        break;
      case SEEDEDGAME:
        newtype = GAME;
        Display[newtype]->setSeed(time(NULL));
        break;
      case GAME:
        Display[newtype]->setSeed(567894);
        //Display[newtype]->setSeed(time(NULL));
        break;
    }
    Display[type]->clean();
    type = newtype;
    Display[type]->setup();
  }
  

 // SDL_FreeSurface(surfaceMessage); 
 
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  prevKeyState[ESC] = keyState[ESC];
  prevMouseBtnState[0] = mouseBtnState[0]; // Left Mouse Button
  
  glEnable (GL_BLEND);
  glBlendFunc (GL_ONE, GL_ONE);
}

void init() {
  if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
    printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    exit(0);
  } else {  
    
    // Use OpenGL 2.1
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    
    settings.Load();
    bool isFullscreen = settings.getFullscreen();
    screenResX = settings.getWindowWidth();
    screenResY = settings.getWindowHeight();

    

    if(isFullscreen) {
      screenResX = 1920;
      screenResY = 1080;
      //Create Window
      gWindow = SDL_CreateWindow("Return-Void", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  screenResX, screenResY, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
      
      // Borderless fullscreen
      //SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
      
      // Fullscreen
      SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
      printf("Entering fullscreen mode\n");
      settings.setFullscreen(true); 
      settings.setResolution(screenResX, screenResY);    
    } else {
      printf("Entering windowed mode\n");
  
      //Create Window
      gWindow = SDL_CreateWindow("Return-Void", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  screenResX, screenResY, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
      
    }    
    TTF_Init();
    settings.Save();  
    SDL_ShowCursor(SDL_DISABLE);
  }
  
  surface  = SDL_GetWindowSurface(gWindow);
  
  aspectRatio = (float)screenResX / screenResY;
  aspectW = (float)SPACE_X_RESOLUTION/(float)screenResX;
  aspectH = (float)SPACE_Y_RESOLUTION/(float)screenResY;
  
  // Create context
  gContext = SDL_GL_CreateContext(gWindow);

  SDL_Init(SDL_INIT_EVERYTHING);
  
  SDL_GL_SetSwapInterval(1);
  
  gluOrtho2D(0.f, SPACE_X_RESOLUTION, 0.f, SPACE_Y_RESOLUTION);
  
  font = TTF_OpenFont("lazy.ttf", 70); //this opens a font style and sets a size
  if(font == NULL)
    exit(0);
  mouseTexture = txt::LoadTexture("Textures/Game/Crosshair.png");
  //Initialize clear color
  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
  
  Display[type]->setup();
}

int main(int argc, char* args[]) {
  init();
  
  bool quit = false;
  
  // Event Handler
  SDL_Event e;
  
  while( !quit ) {
    while( SDL_PollEvent( &e ) != 0 ) {    
      if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
        mouse();
        if(e.type == SDL_MOUSEBUTTONDOWN)
          mouseBtn(e.button.button, BUTTON_DOWN);
        if(e.type == SDL_MOUSEBUTTONUP)
          mouseBtn(e.button.button, BUTTON_UP);
      }
      if(e.type == SDL_KEYDOWN) 
        keyboard(e.key.keysym.sym);      
      if(e.type == SDL_KEYUP) 
        keyboard_up(e.key.keysym.sym);
        
	   //User requests quit
		if( e.type == SDL_QUIT )
		 quit = true;
    }
    display();    
    SDL_GL_SwapWindow(gWindow);
    SDL_Delay(20);
  }
  clean();
  return 0;
}
