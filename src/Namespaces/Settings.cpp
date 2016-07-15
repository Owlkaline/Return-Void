#include "../../include/Namespaces/Settings.h"

Settings::Settings() {
  Load();
}

Settings::~Settings() {

}

void Settings::Load() {
  if(File::check_if_file_exists("data/settings.bin")) {
    printf("Loading Settings\n");
    ifs.open("./data/settings.bin", std::ios::binary);
    version = File::LoadFloat(ifs);
    relativeMovement = File::LoadBool(ifs);
    ifs.close();
  } else {
    printf("Creating settings file\n");
    version = VERSION;
    relativeMovement = false;
    Save();
  }
}

void Settings::Save() {
  printf("Saving settings\n");
  std::ofstream ofs("./data/settings.bin", std::ios::binary);
  File::SaveFloat(ofs, version);
  File::SaveBool(ofs, relativeMovement);
  ofs.close();
}
