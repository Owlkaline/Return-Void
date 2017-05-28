#include "../../include/Menus/SettingsMenu.h"

SettingsMenu::SettingsMenu() {

}

void SettingsMenu::setup() {
  Settings *settings = Settings::instance();
  
  ended = false;
  type = MAINMENU;
  isFullscreen = settings->getFullscreen();
  switch(settings->getWindowWidth()) {
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
  buttons[0]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "Return");
  
  // Save Button
  x = SPACE_X_RESOLUTION/4*2.5 + BUTTONWIDTH/2;
  y = SPACE_Y_RESOLUTION/10 * (1.0) - BUTTONHEIGHT/2;
  buttons.push_back(new Button);
  buttons[1]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "Apply");
  
  // Fullscreen Left Arrow button 
  x = SPACE_X_RESOLUTION/4  * 3 - BUTTONWIDTH - ARROWWIDTH/2;
  y = SPACE_Y_RESOLUTION/10 * (6.5) - BUTTONHEIGHT/2;
  buttons.push_back(new Button);
  buttons[2]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "<");
  
  // Fullscreen Right Arrow button
  x = SPACE_X_RESOLUTION/4 * 3 - ARROWWIDTH/2;
  y = SPACE_Y_RESOLUTION/10 * (6.5) - BUTTONHEIGHT/2;
  buttons.push_back(new Button);
  buttons[3]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), ">");
   
  // Fullscreen Label
  x = SPACE_X_RESOLUTION/4 + BUTTONWIDTH*0.75;
  y = SPACE_Y_RESOLUTION/10 * (6.5) - BUTTONHEIGHT/2;
  lb.push_back(new Label);
  lb[0]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "Fullscreen");

  // Fullscreen True - False Label
  x = SPACE_X_RESOLUTION/4 * 3 - BUTTONWIDTH/2 - ARROWWIDTH/2;
  lb.push_back(new Label);
  if(isFullscreen) {
    lb[1]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "True");
  } else {
    lb[1]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "False");
  }
  
  // Resolution Left Arrow button
  x = SPACE_X_RESOLUTION/4  * 3 - BUTTONWIDTH - ARROWWIDTH*2;
  y = SPACE_Y_RESOLUTION/10 * (5.5) - BUTTONHEIGHT/2;
  buttons.push_back(new Button);
  buttons[4]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "<");
  
  // Resolution Right Arrow button
  x = SPACE_X_RESOLUTION/4 * 3 - ARROWWIDTH/2;
  y = SPACE_Y_RESOLUTION/10 * (5.5) - BUTTONHEIGHT/2;
  buttons.push_back(new Button);
  buttons[5]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), ">");
  
  // Resolution Label
  x = SPACE_X_RESOLUTION/4 + BUTTONWIDTH*0.75;
  y = SPACE_Y_RESOLUTION/10 * (5.5) - BUTTONHEIGHT/2;
  lb.push_back(new Label);
  lb[2]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "Resolution:");
  
  // Resolution idicator Label
  x = SPACE_X_RESOLUTION/4 * 3 - BUTTONWIDTH/2 - ARROWWIDTH*1.25;
  lb.push_back(new Label);
  switch(crntResolution) {
    case 0:
      lb[3]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "800x600");
      break;
    case 1:
      lb[3]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "1280x720");
      break;
    case 2:
      lb[3]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "1920x1080");
  }
  
  if(isFullscreen) {
    lb[2]->disable();
    lb[3]->disable();
    buttons[4]->disable();
    buttons[5]->disable();    
  }
}

void SettingsMenu::restart() {

}

void SettingsMenu::update(float mouseX, float mouseY, float deltaTime, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  Settings *settings = Settings::instance();
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
        settings->setResolution(800, 600);
        break;
      case 1:
        settings->setResolution(1280, 720);
        break;
      case 2:
        settings->setResolution(1920, 1080);
        break;
    }
    if(isFullscreen)
      settings->setResolution(1920, 1080);
    settings->setFullscreen(isFullscreen);
    settings->Save();
  }
  
  if(buttons[2]->Clicked() || buttons[3]->Clicked()) {
    if(isFullscreen) {
      lb[1]->setText("False"); 
      isFullscreen = false;
      lb[2]->enable();
      lb[3]->enable();
      buttons[4]->enable();
      buttons[5]->enable();
    } else {
      lb[1]->setText("True"); 
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
      lb[3]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "800x600");
      break;
    case 1:
      lb[3]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "1280x720");
      break;
    case 2:
      lb[3]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "1920x1080");
    }
  }
  // Right Arrow resolutions
  if(buttons[5]->Clicked()) {
    crntResolution++;
    if(crntResolution > 2) crntResolution = 0;
    switch(crntResolution) {
        case 0:
      lb[3]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "800x600");
      break;
    case 1:
      lb[3]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "1280x720");
      break;
    case 2:
      lb[3]->setup(x, y, 1.5f, glm::vec3(TEXTR, TEXTG, TEXTB), "1920x1080");
    }
  }
}


