#include "../../include/Namespaces/Highscore.h"

Highscore::Highscore() {
//  Load();
}

Highscore::~Highscore() {

}

void Highscore::Load() {

  // check whether application directory in the home diretory exists, if not create it
  # ifdef __linux__
    home = getenv("HOME");
    if (*home.rbegin() != '/') home += '/';
      mkdir((home + ".returnvoid/").c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  # endif

  # ifdef __WIN32__
    TCHAR szAppData[MAX_PATH];
    SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szAppData);
    home = szAppData;
    CreateDirectory((home + ".returnvoid/").c_str(), NULL);
  # endif

  isNewHighscore = false;
  if(File::check_if_file_exists((home + ".returnvoid/Highscore.bin").c_str())) {
    printf("Loading Highscore\n");
    ifs.open((home + ".returnvoid/Highscore.bin").c_str(), std::ios::binary);
    version = File::LoadFloat(ifs);
    if(version != (float)VERSION) {
      ifs.close();
      createNewHighscore();
    } else {    
      for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 6; ++j) {
          name[i][j] = File::LoadChar(ifs);
        }
      }
      for(int i = 0; i < 10; ++i) {
        highscores[i] = File::LoadInt(ifs);
      }
      ifs.close();
    }
  } else {
    createNewHighscore();
  }
}

void Highscore::Save() {
  printf("Saving Highscore\n");
  std::ofstream ofs((home + ".returnvoid/Highscore.bin").c_str(), std::ios::binary);
  File::SaveFloat(ofs, version);
  for(int i = 0; i < 10; ++i) {
    for(int j = 0; j < 6; ++j) {
      File::SaveChar(ofs, name[i][j]);
    }
  }
  for(int i = 0; i < 10; ++i) {
    File::SaveInt(ofs, highscores[i]);
  }
  ofs.close();
}

void Highscore::createNewHighscore() {
  printf("Creating Highscore file\n");
  version = VERSION;   
  highscores[0] = 10000;
  highscores[1] = 8000;
  highscores[2] = 7500;
  highscores[3] = 7000;
  highscores[4] = 5000;
  highscores[5] = 4000;
  highscores[6] = 3500;
  highscores[7] = 3000;
  highscores[8] = 2000;
  highscores[9] = 1000;
  
  name[0][0] = 'A';
  name[0][1] = 'k';
  name[0][2] = 'u';
  name[0][3] = 'm';
  name[0][4] = 'a';
  name[0][5] = ' ';
  
  name[1][0] = 'S';
  name[1][1] = 'a';
  name[1][2] = 't';
  name[1][3] = 'a';
  name[1][4] = 'n';
  name[1][5] = ' ';

  name[2][0] = 'S';
  name[2][1] = 't';
  name[2][2] = 'e';
  name[2][3] = 'v';
  name[2][4] = 'e';
  name[2][5] = 'n';
  
  name[3][0] = 'D';
  name[3][1] = 'a';
  name[3][2] = 'v';
  name[3][3] = 'e';
  name[3][4] = ' ';
  name[3][5] = ' ';

  name[4][0] = 'H';
  name[4][1] = 'a';
  name[4][2] = 'c';
  name[4][3] = 'k';
  name[4][4] = 'e';
  name[4][5] = 'r';

  name[5][0] = '1';
  name[5][1] = '3';
  name[5][2] = '3';
  name[5][3] = '7';
  name[5][4] = ' ';
  name[5][5] = ' ';
  
  name[6][0] = 'G';
  name[6][1] = 'o';
  name[6][2] = 'd';
  name[6][3] = ' ';
  name[6][4] = ' ';
  name[6][5] = ' ';
  
  name[7][0] = 'P';
  name[7][1] = 'a';
  name[7][2] = 'c';
  name[7][3] = 'm';
  name[7][4] = 'a';
  name[7][5] = 'n';
  
  name[8][0] = 'P';
  name[8][1] = 'r';
  name[8][2] = 'o';
  name[8][3] = ' ';
  name[8][4] = ' ';
  name[8][5] = ' ';

  name[9][0] = 'L';
  name[9][1] = 'a';
  name[9][2] = 'g';
  name[9][3] = ' ';
  name[9][4] = ' ';
  name[9][5] = ' ';

  Save();
}
