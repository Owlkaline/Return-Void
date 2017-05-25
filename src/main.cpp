/*
 * main.cpp
 * This file is part of ReturnVoid
 *
 * Copyright (C) 2016 - Akuma
 *
 * ReturnVoid is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * ReturnVoid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ReturnVoid. If not, see <http://www.gnu.org/licenses/>.
 */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "../include/GraphicsHandler.h"

#include "../include/Menus/Shop.h"
#include "../include/Menus/MainMenu.h"
#include "../include/Menus/SettingsMenu.h"
#include "../include/Menus/HighscoreScreen.h"

#include "../include/GameTypes/Game.h"
#include "../include/GameTypes/Menu.h"
#include "../include/GameTypes/Story.h"

#include "../include/Namespaces/Settings.h"
#include "../include/Namespaces/Highscore.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT =786;

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

//Keeps the current key state, keeps the key state of the previous key state
unsigned int  specialKey[5];
unsigned int  mouseBtnState[3];
unsigned int  prevSpeicalKey[5];
unsigned int  prevMouseBtnState[3];

unsigned char keyState[350];
unsigned char prevKeyState[350];

GLuint mouseTexture;

DisplayManager* Display[6] = { new MainMenu(), new Game(), new SettingsMenu(), new Shop(), new HighscoreScreen(), new Story() };

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
  // Gets the relative mouse position to the grid coords rather than physics window
  mouseY = SPACE_Y_RESOLUTION-ypos*SPACE_Y_RESOLUTION/SCREEN_HEIGHT;
  mouseX = xpos*SPACE_X_RESOLUTION/SCREEN_WIDTH;
}

//Updates what keys are pressed
void keyboard(int key) {
  //printf("key: %d\n", key);
  keyState[key] = BUTTON_DOWN;
}

//Updates what keys are released
void keyboard_up(int key) {
    keyState[key] = BUTTON_UP;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {    
  if(action == GLFW_PRESS) {
    keyboard(key);
  }
  if(action == GLFW_RELEASE) {
    keyboard_up(key);
  }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
  mouseBtnState[button] = action;
  //  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
  //      popup_menu();
}
  

void drawCursor() {
  if(type != ENDLESSGAME) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mouseTexture);
    // Nice blue #1e00d5
    //glColor3f(0.117647059f, 0, 0.835294197f);
    glColor4f(1, 0.643137255, 0, 1.0f);
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
  Settings *settings = Settings::instance();
  settings->destroy();
  glfwTerminate();
}

void display(GLFWwindow* window, GraphicsHandler* graphics, float deltaTime) {      
  glClear(GL_COLOR_BUFFER_BIT); //Wipes screen clear

 
  glClearColor(0.0f, 0.0f, 0.0f, 255.0f);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//Blends colours with alpha
  
  
  //Texture options
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  //glColor4ub(255,255,255,255); //sets full colours and alpha

  Display[type]->update(mouseX, mouseY, deltaTime, mouseBtnState, prevMouseBtnState, keyState, prevKeyState);
  Display[type]->draw(graphics);
  
  graphics->drawObject(glm::vec2(mouseX, mouseY), glm::vec2(40, 40), "cursor");
  
  if(Display[type]->hasEnded()) {
    int newtype = Display[type]->getEndType();
    switch(newtype) {
      case EXIT:
        glfwSetWindowShouldClose(window, true);
        clean();
        exit(0);
        break;
      case ENDLESSGAME:
        Display[newtype]->setSeed(567894);
        break;
      case STORY:
       // Display[newtype]->setSeed(time(NULL));
        //Display[newtype]->setSeed(time(NULL));
        break;
    }
    Display[type]->clean();
    type = newtype;
    Display[type]->setup();
  }
 
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  prevKeyState[ESC] = keyState[ESC];
  prevMouseBtnState[0] = mouseBtnState[0]; // Left Mouse Button
  
  glEnable (GL_BLEND);
  glBlendFunc (GL_ONE, GL_ONE);
}

GLFWwindow* init() {
  Settings *settings =  Settings::init();
  Highscore *highscore = Highscore::init();
    
  /* Initialize the library */
  GLFWwindow* window;
  if (!glfwInit()) {
    glfwSetWindowShouldClose(window, true);
    return window;
  }
  // Use OpenGL 2.1    
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
  bool isFullscreen = settings->getFullscreen();
  screenResX = settings->getWindowWidth();
  screenResY = settings->getWindowHeight();

  /* Create a windowed mode window and its OpenGL context */

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  if(!isFullscreen) {
    // Borderless fullscreen
    // const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    // glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    // glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    // glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    // glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    // GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);
    
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    screenResX = mode->width;
    screenResY = mode->height;
    
    window = glfwCreateWindow(SPACE_X_RESOLUTION, SPACE_Y_RESOLUTION, "Return-Void", glfwGetPrimaryMonitor(), NULL);

    printf("Entering fullscreen mode\n");
    settings->setFullscreen(true); 
  } else {
    printf("Entering windowed mode %dx%d\n", screenResX, screenResY);
    screenResX = SCREEN_WIDTH;
    screenResY = SCREEN_HEIGHT;
    //Create Window
    window = glfwCreateWindow(screenResX, screenResY, "Return-Void", NULL, NULL);
      
  }
  settings->setResolution(screenResX, screenResY);    
  
  if (!window) {
    glfwTerminate();
    glfwSetWindowShouldClose(window, true);
    return window;
  }  
  
  aspectRatio = (float)screenResX / (float)screenResY;
  aspectW = (float)SPACE_X_RESOLUTION/(float)screenResX;
  aspectH = (float)SPACE_Y_RESOLUTION/(float)screenResY;

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  return window;
}

void loadAllTextures(GraphicsHandler* graphics) {
  graphics->loadTexture("cursor", "Textures/Game/Crosshair.png");
  
  // Enemy Textures
  graphics->loadTexture("BasicEnemy", "Textures/Game/Enemies/BasicEnemy.png");
  graphics->loadTexture("HypnoEnemy","Textures/Game/Enemies/HypnoEnemy.png");
  graphics->loadTexture("AlphaOne","Textures/Game/Enemies/AlphaOne.png");
  graphics->loadTexture("DotEnemy","Textures/Game/Enemies/DotEnemy.png");

  graphics->loadTexture("CStarShip","Textures/Game/Enemies/CorruptedStarShip.png");
  graphics->loadTexture("CStarShip1","Textures/Game/Enemies/CorruptedStarShipDmg1.png");
  graphics->loadTexture("CStarShip2","Textures/Game/Enemies/CorruptedStarShipDmg2.png");
  graphics->loadTexture("CStarShip3","Textures/Game/Enemies/CorruptedStarShipDmg3.png");
  graphics->loadTexture("CStarShip4","Textures/Game/Enemies/CorruptedStarShipDmg4.png");
  
  // Player Textures
  graphics->loadTexture("FighterShip1", "Textures/Game/Ships/FighterShip1.png");
  graphics->loadTexture("FighterShip2","Textures/Game/Ships/FighterShip2.png");
  graphics->loadTexture("FighterShip3","Textures/Game/Ships/FighterShip3.png");
  graphics->loadTexture("GalacticShip","Textures/Game/Ships/GalacticShip.png");
  graphics->loadTexture("HeroShip","Textures/Game/Ships/HeroShip3.png");
    
  // Weapon Textures
  graphics->loadTexture("BluePlasma","Textures/Game/Weapons/BluePlasma.png");
  graphics->loadTexture("GreenPlasma","Textures/Game/Weapons/GreenPlasma.png");
  graphics->loadTexture("RedPlasma","Textures/Game/Weapons/RedPlasma.png");
  graphics->loadTexture("PurplePlasma","Textures/Game/Weapons/PurplePlasma.png");
  graphics->loadTexture("Spiral","Textures/Game/Weapons/Spiral.png");
  graphics->loadTexture("DotBullet","Textures/Game/Weapons/DotBullet.png");
  graphics->loadTexture("AlphaOnePlasma","Textures/Game/Weapons/AlphaOnePlasma.png");
  
  // HUD textures
  graphics->loadTexture("HealthBarBase", "Textures/Game/Misc/HealthBarBase.png");
  graphics->loadTexture("HealthBar", "Textures/Game/Misc/HealthBar.png");
  graphics->loadTexture("ShieldBar", "Textures/Game/Misc/ShieldBar.png");
  
  graphics->loadTexture("Shield", "Textures/Game/Ships/Shield.png");
  graphics->loadTexture("ShieldRipple1", "Textures/Game/Ships/ShieldRipple1.png");
  graphics->loadTexture("ShieldRipple2", "Textures/Game/Ships/ShieldRipple2.png");
  graphics->loadTexture("ShieldRipple3", "Textures/Game/Ships/ShieldRipple3.png");
  graphics->loadTexture("ShieldRipple4", "Textures/Game/Ships/ShieldRipple4.png");
  graphics->loadTexture("ShieldRipple5", "Textures/Game/Ships/ShieldRipple5.png");
  
  // Mount textures
  graphics->loadTexture("BasicMount","Textures/Game/Mounts/BasicMount.png");  
  graphics->loadTexture("BasicMountBright", "Textures/Game/Mounts/BasicMountBright.png");
  graphics->loadTexture("PurpleMount", "Textures/Game/Mounts/PurpleMount.png");
  graphics->loadTexture("AlphaOneMount", "Textures/Game/Mounts/AlphaOneMount.png");  
  graphics->loadTexture("HeroMount1", "Textures/Game/Ships/HeroMount1.png");
  graphics->loadTexture("HeroMount2", "Textures/Game/Ships/HeroMount2.png");
  graphics->loadTexture("HeroMount3", "Textures/Game/Ships/HeroMount3.png");
  graphics->loadTexture("HeroMount4", "Textures/Game/Ships/HeroMount4.png");
  graphics->loadTexture("HypnoMountLeft", "Textures/Game/Mounts/HypnoMountLeft.png");
  graphics->loadTexture("HypnoMountRight", "Textures/Game/Mounts/HypnoMountRight.png");
  
  // Powerup texturess
  graphics->loadTexture("PowerupCoin", "Textures/Game/Powerups/Coin.png");
  graphics->loadTexture("PowerupHealth", "Textures/Game/Powerups/Health.png");
  graphics->loadTexture("PowerupShield", "Textures/Game/Powerups/Shield.png");
  graphics->loadTexture("Boost", "Textures/Game/Misc/Boost.png");
  
  // TOBEREMOVED
  // Menu stuff - For now 
  graphics->loadTexture("LeftArrow", "Textures/Menu/Misc/LeftArrow.png");
  graphics->loadTexture("RightArrow", "Textures/Menu/Misc/RightArrow.png");
  
  // Extra
  graphics->loadTexture("Edge", "Textures/Game/Mounts/BasicMount2.png");
  graphics->loadTexture("MenuBackground", "Textures/Menu/Background.png");
  graphics->loadTexture("Background", "Textures/Game/Background.png");
  graphics->loadTexture("BoxBackground", "Textures/Menu/ShopMenu/Boxbackground.png");
  graphics->loadTexture("window", "Textures/Menu/GameMenus/Window.png");
}

int main(int argc, char* args[]) {
  
  GLFWwindow* window = init();
  
  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
  {
    std::cout << "Failed to initialize GLEW\n";
    return -1;
  }
  
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, cursor_pos_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  
  //mouseTexture = txt::LoadTexture("Textures/Game/Crosshair.png");
  GraphicsHandler graphics;
  graphics.loadShaders("./Shaders/shader.vert", "./Shaders/shader.frag", "basic");
  graphics.loadShaders("./Shaders/font.vert", "./Shaders/font.frag", "text");
  graphics.useShader("basic");
  graphics.init(SPACE_X_RESOLUTION, SPACE_Y_RESOLUTION);
  graphics.initText("DarkCrystal.ttf", "text");
  loadAllTextures(&graphics);
  
  //Initialize clear color
  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
  
  Display[type]->setup();
  
  double lastTime = glfwGetTime();
  while(!glfwWindowShouldClose(window)) {    
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime)  * 50;
    lastTime = currentTime;
    
    glfwPollEvents();
    graphics.useShader("basic");
    display(window, &graphics, deltaTime);  
    //graphics.drawText("It Fucking works, ya cunt", glm::vec2(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2), 1.5f, glm::vec3(0.5f, 0.5f, 1.0f));
    glfwSwapBuffers(window);
  }
  clean();
  glfwTerminate();
  return 0;
}
