#include "../../include/Menus/HighscoreScreen.h"

void HighscoreScreen::draw() {
  Quit.draw();
  Retry.draw();
  lbScore.draw();
  lbTitle.draw();
}

void HighscoreScreen::setup() {
  float width = 247;
  float height = 95;
  Retry.setup(SPACE_X_RESOLUTION/4*3, SPACE_Y_RESOLUTION/10, width, height, -1);
  Quit.setup(SPACE_X_RESOLUTION/4 +width/2, SPACE_Y_RESOLUTION/10, width, height, -1);
  
  lbTitle.setup(SPACE_X_RESOLUTION/2+width/6, SPACE_Y_RESOLUTION/5*4, 0.4);
  lbScore.setup(SPACE_X_RESOLUTION/2+width/6, SPACE_Y_RESOLUTION/5*4 + height, 0.4);

  std::string str = "Highscores";
  lbTitle.setText(str.c_str(), str.length());
  str = "Your Score: ";
  lbScore.setText(str.c_str(), str.length());
  // #f08600 R 240 G 134 B 0
  float R = 0.941176471;
  float G = 0.525490246;
  float B = 0;

  lbTitle.setColour(R, G, B);
  lbScore.setColour(R, G, B);
  
  Retry.setTexture((char*)"Textures/Menu/Resume.png");
  Quit.setTexture((char*)"Textures/Menu/Quit.png");
} 
 
void HighscoreScreen::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState) {
  ended = false;
  Retry.update(mouseX, mouseY, mouseBtnState, prevMouseBtnState);
  Quit.update(mouseX, mouseY, mouseBtnState, prevMouseBtnState);

  if(Retry.Clicked()) {
  }
  if(Quit.Clicked()) {
    ended = true;
  }
}

void HighscoreScreen::setScore(int score) {
  std::stringstream ss;
  ss << score;
  std::string strScore = "Your score: " + ss.str();
  lbScore.setText(strScore.c_str(), strScore.length());
  LoadHighscores(score);
}

void HighscoreScreen::LoadHighscores(int score) {
  if (File::check_if_file_exists("data/highscore.bin")) {
    printf("\nLoading highscore\n");
    std::ifstream ifs("./data/highscore.bin", std::ios::binary);
    char str[6];
    for(int i = 0; i < 6; ++i)
      str[i] = File::LoadChar(ifs);
    int newScore = File::LoadInt(ifs);
    
    for(int i = 0; i < 6; ++i)
      printf("%c", str[i]);
    printf(", %d\n", newScore);
    
    if(newScore > score) {
      std::ofstream ofs("./data/highscore.bin", std::ios::binary);
    
      File::SaveChar(ofs, 'N');
      File::SaveChar(ofs, 'a');
      File::SaveChar(ofs, 'm');
      File::SaveChar(ofs, 'e');
      File::SaveChar(ofs, ' ');
      File::SaveChar(ofs, ' ');
      File::SaveInt(ofs, newScore);
    }
  } else {
    printf("\nCreating new highscore file\n");
    std::ofstream ofs("./data/highscore.bin", std::ios::binary);
    
    File::SaveChar(ofs, 'A');
    File::SaveChar(ofs, 'k');
    File::SaveChar(ofs, 'u');
    File::SaveChar(ofs, 'm');
    File::SaveChar(ofs, 'a');
    File::SaveChar(ofs, ' ');
    File::SaveInt(ofs, 10000);
  }
}

bool HighscoreScreen::hasEnded() { return ended; }
