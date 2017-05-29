#ifndef GRAPHICSHANDLER
#define GRAPHICSHANDLER

// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <stdexcept>

#include "./Namespaces/LoadTexture.h"

struct Character {
  GLuint TextureID;
  glm::ivec2 Size;
  glm::ivec2 Bearing;
  GLuint Advance;
};

class GraphicsHandler {
  public:
    GraphicsHandler();
    ~GraphicsHandler();
    
    void init(int width, int height);
    void initText(const char* location, const char * vertex_file_path,const char * fragment_file_path, std::string referencename);
    void clean();
    
    // Call once per loop (At start), or anytime you switch shaders
    void useShader(std::string shader);

    // Loads texture ready to use, with reference name
    void loadTexture(std::string texture, const char * filename);
    void loadShaders(const char * vertex_file_path,const char * fragment_file_path, std::string shader);
    
    void removeShader(std::string name);
    void removeTexture(std::string name);
    
    void drawText(std::string text, glm::vec2 position, GLfloat scale, glm::vec3 color, std::string referencename);
    void drawText(std::string text, glm::vec2 position, GLfloat scale, glm::vec4 color, std::string referencename);
    
    // Draws object at position x/y, with specified size, rotated 0 degrees, full colour
    void drawObject(glm::vec2 position, glm::vec2 size, std::string texture);
    
    void drawObject(glm::vec2 position, glm::vec2 size, GLfloat rotate, std::string texture);
    void drawObject(glm::vec2 position, glm::vec2 size, GLfloat rotate, GLfloat transparency, std::string texture);
    
    void drawObject(glm::vec2 position, glm::vec2 size, glm::vec3 colour, std::string name);
    void drawObject(glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 colour, std::string texture);

    void drawObject(glm::vec2 position, glm::vec2 size, glm::vec4 colour, std::string texture);
    void drawObject(glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec4 colour, std::string texture);
  protected:
    void draw();    
    void transformModel(glm::vec3 position, glm::vec2 size, GLfloat rotation, glm::vec4 colour);

    GLuint getShader(std::string shader);
    GLuint getTexture(std::string texture);
    
    std::string crntShader;
    GLuint quadVAO;
    GLuint textVAO, textVBO;
    
    glm::vec2 window;
    
    std::map<std::string, GLuint> textures;
    std::map<std::string, GLuint> shaders;
    
    std::map<std::string, std::map<GLchar, Character>> Fonts;

    FT_Library ft;
    FT_Face face;
    float fontSize;
};

#endif
