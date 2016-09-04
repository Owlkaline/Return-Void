#include "../../include/Namespaces/Settings.h"

Settings::Settings() {
//  Load();
}

Settings::~Settings() {

}

void Settings::firstLoad() {
  Load();
  crntWindowWidth = windowWidth;
  crntWindowHeight = windowHeight;
}

void Settings::Load() {

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

  if(File::check_if_file_exists((home + ".returnvoid/settings.bin").c_str())) {
    printf("Loading Settings\n");
    ifs.open((home + ".returnvoid/settings.bin").c_str(), std::ios::binary);
    version = File::LoadFloat(ifs);
    if(version != (float)VERSION) {
      createNewSettings();
    } else {
      fullscreen = File::LoadBool(ifs);
      windowWidth = File::LoadInt(ifs);
      windowHeight = File::LoadInt(ifs);
      crntWindowWidth = File::LoadInt(ifs);
      crntWindowHeight = File::LoadInt(ifs);
      ifs.close();
    }
  } else {
    createNewSettings();
  }
}

void Settings::Save() {
  printf("Saving settings\n");
  std::ofstream ofs((home + ".returnvoid/settings.bin").c_str(), std::ios::binary);
  File::SaveFloat(ofs, version);
  File::SaveBool(ofs, fullscreen);
  File::SaveInt(ofs, windowWidth);
  File::SaveInt(ofs, windowHeight);
  File::SaveInt(ofs, crntWindowWidth);
  File::SaveInt(ofs, crntWindowHeight);
  ofs.close();
}

void Settings::createNewSettings() {
  printf("Creating settings file\n");
  version = VERSION;   
  fullscreen = true;
  windowWidth = 1920;
  windowHeight = 1080;
  crntWindowWidth = windowWidth;
  crntWindowHeight = windowHeight;
  Save();
}

