#include "../../include/Namespaces/Profile.h"

Profile::Profile() {

}

Profile::~Profile() {

}

void Profile::Load(char* filename) {

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

  this->filename = filename;  
  str = (home + ".returnvoid/").c_str();
  str += filename;
  str += ".save";
  if(File::check_if_file_exists(str)) {
    printf("Loading Profile\n");
    ifs.open(str.c_str(), std::ios::binary);
    version = File::LoadFloat(ifs);
    if(version != (float)VERSION) {
      ifs.close();
      createNewProfile();
    } else {    
      coins = File::LoadInt(ifs);
      selectedShip = File::LoadInt(ifs);
      for(int i = 0; i < 6; ++i)
        shipsUnlocked[i] = File::LoadBool(ifs);
      for(int i = 0; i < 6; ++i)
        shipsBought[i] = File::LoadBool(ifs);
      ifs.close();
    }
  } else {
    createNewProfile();
  }
}

void Profile::createNewProfile() {
  printf("Creating Profile file\n");
  version = VERSION;   
  coins = 0;
  selectedShip = 0;
  shipsUnlocked[0] = true;
  shipsBought[0] = true;
  shipsUnlocked[1] = true;
  shipsBought[1] = false;
  
  for(int i = 2; i < 6; ++i) {
    shipsUnlocked[i] = false; 
    shipsBought[i] = false;
  }  
  Save();
}

void Profile::Save() {
  printf("Saving Profile\n");
  std::ofstream ofs(str.c_str(), std::ios::binary);
  File::SaveFloat(ofs, version);
  File::SaveInt(ofs, coins);
  File::SaveInt(ofs, selectedShip);
  
  for(int i = 0; i < 6; ++i)
    File::SaveBool(ofs, shipsUnlocked[i]);  
    
  for(int i = 0; i < 6; ++i)
    File::SaveBool(ofs, shipsBought[i]);  
  ofs.close();
}
