#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>

namespace File {
    void skipData(std::ifstream& inf, size_t a);
    void skipData(std::ofstream& of, size_t a);

    void SaveInt(std::ofstream& of, int var);   
    void SaveChar(std::ofstream& of, char var);
    void SaveBool(std::ofstream& of, bool var);
    void SaveFloat(std::ofstream& of, float var);
    void SaveString(std::ofstream& of, std::string var);
    
    bool LoadBool(std::ifstream& inf);
    bool check_if_file_exists (const std::string& name);
     
    int LoadInt(std::ifstream& inf);
    
    float LoadFloat(std::ifstream& inf);
    
    char LoadChar(std::ifstream& inf);
    
    std::string LoadString(std::ifstream& inf);
};

#endif
