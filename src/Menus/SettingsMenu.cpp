#include "../../include/Menus/SettingsMenu.h"

SettingsMenu::SettingsMenu() {

}

void SettingsMenu::setup() {
  settings.Load();
  ended = false;
  type = MAINMENU;
  isFullscreen = settings.getFullscreen();
  switch(settings.getWindowWidth()) {
    case 800:
      crntResolution = 0;
      break;
    case 1280:
      crntResolution = 1;
      break;
    case 1920:
      crntResolution = 2;
      break;
    default:
      crntResolution = 2;
      break;
  }
   
  // Return Button
  x = SPACE_X_RESOLUTION/4 + BUTTONWIDTH/2;
  y = SPACE_Y_RESOLUTION/10 * (1.0) - BUTTONHEIGHT/2;
  buttons.push_back(new Button);
  buttons[0]->setup(x, y, BUTTONWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/Misc/Return.png");
  
  // Save Button
  x = SPACE_X_RESOLUTION/4*2.5 + BUTTONWIDTH/2;
  y = SPACE_Y_RESOLUTION/10 * (1.0) - BUTTONHEIGHT/2;
  buttons.push_back(new Button);
  buttons[1]->setup(x, y, BUTTONWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/SettingsMenu/Apply.png");
  
  // Fullscreen Left Arrow button 
  x = SPACE_X_RESOLUTION/4  * 3 - BUTTONWIDTH - ARROWWIDTH/2;
  y = SPACE_Y_RESOLUTION/10 * (6.5) - BUTTONHEIGHT/2;
  buttons.push_back(new Button);
  buttons[2]->setup(x, y, ARROWWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/Misc/LeftArrow.png");
  
  // Fullscreen Right Arrow button
  x = SPACE_X_RESOLUTION/4 * 3 - ARROWWIDTH/2;
  y = SPACE_Y_RESOLUTION/10 * (6.5) - BUTTONHEIGHT/2;
  buttons.push_back(new Button);
  buttons[3]->setup(x, y, ARROWWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/Misc/RightArrow.png");
   
  // Fullscreen Label
  x = SPACE_X_RESOLUTION/4 + BUTTONWIDTH*0.75;
  y = SPACE_Y_RESOLUTION/10 * (6.5) - BUTTONHEIGHT/2;
  lb.push_back(new Label);
  lb[0]->setup(x, y, BUTTONWIDTH*1.5, BUTTONHEIGHT, (char*)"Textures/Menu/SettingsMenu/Fullscreen.png");

  // Fullscreen True - False Label
  x = SPACE_X_RESOLUTION/4 * 3 - BUTTONWIDTH/2 - ARROWWIDTH/2;
  lb.push_back(new Label);
  if(isFullscreen) {
    lb[1]->setup(x, y, BUTTONWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/Misc/True.png");
  } else {
    lb[1]->setup(x, y, BUTTONWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/Misc/False.png");
  }
  
  // Resolution Left Arrow button
  x = SPACE_X_RESOLUTION/4  * 3 - BUTTONWIDTH - ARROWWIDTH*2;
  y = SPACE_Y_RESOLUTION/10 * (5.5) - BUTTONHEIGHT/2;
  buttons.push_back(new Button);
  buttons[4]->setup(x, y, ARROWWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/Misc/LeftArrow.png");
  
  // Resolution Right Arrow button
  x = SPACE_X_RESOLUTION/4 * 3 - ARROWWIDTH/2;
  y = SPACE_Y_RESOLUTION/10 * (5.5) - BUTTONHEIGHT/2;
  buttons.push_back(new Button);
  buttons[5]->setup(x, y, ARROWWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/Misc/RightArrow.png");
  
  // Resolution Label
  x = SPACE_X_RESOLUTION/4 + BUTTONWIDTH*0.75;
  y = SPACE_Y_RESOLUTION/10 * (5.5) - BUTTONHEIGHT/2;
  lb.push_back(new Label);
  lb[2]->setup(x, y, BUTTONWIDTH*1.5, BUTTONHEIGHT, (char*)"Textures/Menu/SettingsMenu/Resolution.png");
  
  // Resolution idicator Label
  x = SPACE_X_RESOLUTION/4 * 3 - BUTTONWIDTH/2 - ARROWWIDTH*1.25;
  lb.push_back(new Label);
  switch(crntResolution) {
    case 0:
      lb[3]->setup(x, y, BUTTONWIDTH*1.5, BUTTONHEIGHT, (char*)"Textures/Menu/SettingsMenu/800x600.png");
      break;
    case 1:
      lb[3]->setup(x, y, BUTTONWIDTH*1.5, BUTTONHEIGHT, (char*)"Textures/Menu/SettingsMenu/1280x720.png");
      break;
    case 2:
      lb[3]->setup(x, y, BUTTONWIDTH*1.5, BUTTONHEIGHT, (char*)"Textures/Menu/SettingsMenu/1920x1080.png");
  }
  
  if(isFullscreen) {
    lb[2]->disable();
    lb[3]->disable();
    buttons[4]->disable();
    buttons[5]->disable();    
  }
  
  background = txt::LoadTexture("Textures/Menu/Background.png");
}

void SettingsMenu::restart() {

}

void SettingsMenu::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
    prevKeyState[ESC] = keyState[ESC];
    type = MAINMENU;
    ended = true;
  }
  
  for(unsigned int i = 0; i < buttons.size(); ++i)
    buttons[i]->update(mouseX, mouseY, mouseBtnState, prevMouseBtnState);
  
  if(buttons[0]->Clicked()) {
    type = MAINMENU;
    ended = true;
  } 
  
  if(buttons[1]->Clicked()) {
    switch(crntResolution) {
      case 0:
        settings.setResolution(800, 600);
        break;
      case 1:
        settings.setResolution(1280, 720);
        break;
      case 2:
        settings.setResolution(1920, 1080);
        break;
    }
    settings.setFullscreen(isFullscreen);
    settings.Save();
  }
  
  if(buttons[2]->Clicked() || buttons[3]->Clicked()) {
    if(isFullscreen) {
      lb[1]->setTexture((char*)"Textures/Menu/Misc/False.png"); 
      isFullscreen = false;
      lb[2]->enable();
      lb[3]->enable();
      buttons[4]->enable();
      buttons[5]->enable();
    } else {
      lb[1]->setTexture((char*)"Textures/Menu/Misc/True.png"); 
      isFullscreen = true;
      lb[2]->disable();
      lb[3]->disable();
      buttons[4]->disable();
      buttons[5]->disable();
    }
  }
  // Left Arrow resolutions
  if(buttons[4]->Clicked()) {
    crntResolution--;
    if(crntResolution < 0) crntResolution = 2;
    switch(crntResolution) {
    case 0:
      lb[3]->setup(x, y, BUTTONWIDTH*1.5, BUTTONHEIGHT, (char*)"Textures/Menu/SettingsMenu/800x600.png");
      break;
    case 1:
      lb[3]->setup(x, y, BUTTONWIDTH*1.5, BUTTONHEIGHT, (char*)"Textures/Menu/SettingsMenu/1280x720.png");
      break;
    case 2:
      lb[3]->setup(x, y, BUTTONWIDTH*1.5, BUTTONHEIGHT, (char*)"Textures/Menu/SettingsMenu/1920x1080.png");
    }
  }
  // Right Arrow resolutions
  if(buttons[5]->Clicked()) {
    crntResolution++;
    if(crntResolution > 2) crntResolution = 0;
    switch(crntResolution) {
        case 0:
      lb[3]->setup(x, y, BUTTONWIDTH*1.5, BUTTONHEIGHT, (char*)"Textures/Menu/SettingsMenu/800x600.png");
      break;
    case 1:
      lb[3]->setup(x, y, BUTTONWIDTH*1.5, BUTTONHEIGHT, (char*)"Textures/Menu/SettingsMenu/1280x720.png");
      break;
    case 2:
      lb[3]->setup(x, y, BUTTONWIDTH*1.5, BUTTONHEIGHT, (char*)"Textures/Menu/SettingsMenu/1920x1080.png");
    }
  }
}


