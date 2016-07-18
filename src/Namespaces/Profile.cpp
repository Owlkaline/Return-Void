#include "../../include/Namespaces/Profile.h"

Profile::Profile() {
  Load();
}

Profile::~Profile() {

}

void Profile::Load() {
  if(File::check_if_file_exists("data/Profile.save")) {
    printf("Loading Profile\n");
    ifs.open("./data/Profile.save", std::ios::binary);
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

void Profile::Save() {
  printf("Saving Profile\n");
  std::ofstream ofs("./data/Profile.save", std::ios::binary);
  File::SaveFloat(ofs, version);
  File::SaveInt(ofs, coins);
  File::SaveInt(ofs, selectedShip);
  
  for(int i = 0; i < 6; ++i)
    File::SaveBool(ofs, shipsUnlocked[i]);  
    
  for(int i = 0; i < 6; ++i)
    File::SaveBool(ofs, shipsBought[i]);  
  ofs.close();
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
