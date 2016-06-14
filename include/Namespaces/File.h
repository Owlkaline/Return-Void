#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>

namespace File {

    bool check_if_file_exists (const std::string& name);
    
    int LoadInt(std::ifstream& inf);
    float LoadFloat(std::ifstream& inf);
    char LoadChar(std::ifstream& inf);
    std::string LoadString(std::ifstream& inf);
    bool LoadBool(std::ifstream& inf);    

    void SaveInt(std::ofstream& of, int var);
    void SaveFloat(std::ofstream& of, float var);
    void SaveChar(std::ofstream& of, char var);
    void SaveString(std::ofstream& of, std::string var);
    void SaveBool(std::ofstream& of, bool var);
};

#endif
