#include "../../include/Namespaces/File.h"

bool File::check_if_file_exists (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

void File::skipData(std::ifstream& inf, size_t a) {
  inf.read((char* )&a, sizeof(a));
}

void File::skipData(std::ofstream& of, size_t a) {
  of.write((char* )&a, sizeof(a));
}

int File::LoadInt(std::ifstream& inf) {
  int var;
  inf.read((char* )&var, sizeof(var));
  return var;
}

float File::LoadFloat(std::ifstream& inf) {
  float var;
  inf.read((char* )&var, sizeof(var));
  return var;
}

char File::LoadChar(std::ifstream& inf) {
  char var;
  inf.read((char* )&var, sizeof(var));
  return var;
}

std::string File::LoadString(std::ifstream& inf) {
  std::string var;
  inf.read((char* )&var, sizeof(var));
  return var;
}

bool File::LoadBool(std::ifstream& inf) {
  bool var;
  inf.read((char* )&var, sizeof(var));
  return var;
}

void File::SaveInt(std::ofstream& of, int var) {
  of.write((char* )&var, sizeof(var));
}
  
void File::SaveFloat(std::ofstream& of, float var) {
  of.write((char* )&var, sizeof(var));
}

void File::SaveChar(std::ofstream& of, char var) {
  of.write(&var, sizeof(var));
}

void File::SaveString(std::ofstream& of, std::string var) {
  of.write((char* )&var, sizeof(var));
}

void File::SaveBool(std::ofstream& of, bool var) {
  of.write((char* )&var, sizeof(var));
}

      



