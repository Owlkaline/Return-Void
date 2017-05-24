#include "../include/GraphicsHandler.h"

GraphicsHandler::GraphicsHandler() {

}

GraphicsHandler::~GraphicsHandler() {
  clean();
}

void GraphicsHandler::clean() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &quadVAO);
  
  shaders.clear();
  textures.clear();
}

void GraphicsHandler::useShader(std::string name) {
  glUseProgram(getShader(name));
  crntShader = name;
}

void GraphicsHandler::init(int width, int height) {

  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width),
                                   static_cast<GLfloat>(height), 0.0f, -0.1f, 1.0f);

  window = glm::vec2(width, height);

  useShader(crntShader);
  glUniform1i(glGetUniformLocation(getShader(crntShader), (const GLchar*)"image"), 0);
  glUniformMatrix4fv(glGetUniformLocation(getShader(crntShader), (const GLchar*)"projection"), 1, GL_FALSE, glm::value_ptr(projection));


  GLuint VBO;
  GLfloat vertices[] = {
    // Pos      // Tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };

  glGenVertexArrays(1, &quadVAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(quadVAO);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (GLvoid*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void GraphicsHandler::initText(const char* fontname, std::string shadername) {
  // Text Init
  textShader = shadername;
  useShader(textShader);
  
  if (FT_Init_FreeType(&ft))
    throw std::runtime_error("ERROR::FREETYPE: Could not init FreeType Library");
  
  if (FT_New_Face(ft, fontname, 0, &face))
    std::runtime_error("ERROR::FREETYPE: Failed to load font");
  
  FT_Set_Pixel_Sizes(face, 0, 48);
  
  if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    std::runtime_error("ERROR::FREETYTPE: Failed to load Glyph");
  
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  for (GLubyte c = 0; c < 128; c++) {
    if(FT_Load_Char(face, c, FT_LOAD_RENDER)) 
      throw std::runtime_error("ERROR::FREETYTPE: Failed to load Glyph");
    
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer
    );
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    Character character {
      texture, 
      glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
      face->glyph->advance.x
    };
    Characters.insert(std::pair<GLchar, Character>(c, character));
  }
  
  FT_Done_Face(face);
  FT_Done_FreeType(ft);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(window.x),
                                    0.0f, static_cast<GLfloat>(window.y));
  glUniformMatrix4fv(glGetUniformLocation(getShader(textShader), (const GLchar*)"projection"), 1, GL_FALSE, glm::value_ptr(projection));
  
  glGenVertexArrays(1, &textVAO);
  glGenBuffers(1, &textVBO);
  glBindVertexArray(textVAO);
  glBindBuffer(GL_ARRAY_BUFFER, textVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0); 
}

void GraphicsHandler::drawText(std::string text, glm::vec2 position, GLfloat scale, glm::vec3 color) {
  useShader(textShader);
  glUniform3f(glGetUniformLocation(getShader(textShader), "fragColour"), color.x, color.y, color.z);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(textVAO);

  // Iterate through all characters
  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++) {
    Character ch = Characters[*c];

    GLfloat xpos = position.x + ch.Bearing.x * scale;
    GLfloat ypos = position.y - (ch.Size.y - ch.Bearing.y) * scale;

    GLfloat w = ch.Size.x * scale;
    GLfloat h = ch.Size.y * scale;

    // Update VBO for each character
    GLfloat vertices[6][4] = {
      { xpos,     ypos + h,   0.0, 0.0 },
      { xpos,     ypos,       0.0, 1.0 },
      { xpos + w, ypos,       1.0, 1.0 },

      { xpos,     ypos + h,   0.0, 0.0 },
      { xpos + w, ypos,       1.0, 1.0 },
      { xpos + w, ypos + h,   1.0, 0.0 }
    };
    
    // Render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.TextureID);
    
    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    position.x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
  }
  
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void GraphicsHandler::drawObject(glm::vec2 position, glm::vec2 size, std::string name) {

  transformModel(glm::vec3(position.x-size.x*0.5f, window.y-position.y-size.y*0.5f, 0.0f),
                 size,
                 0.0f,
                 glm::vec3(1.0f, 1.0f, 1.0f));

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, getTexture(name));

  draw();
}

void GraphicsHandler::drawObject(glm::vec2 position, glm::vec2 size, GLfloat rotate, std::string name) {

  transformModel(glm::vec3(position.x-size.x*0.5f, window.y-position.y-size.y*0.5f, 0.0f),
                 size,
                 rotate,
                 glm::vec3(1.0f, 1.0f, 1.0f));
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, getTexture(name));

  draw();
}

void GraphicsHandler::drawObject(glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 colour, std::string name) {
  transformModel(glm::vec3(position.x-size.x*0.5f, window.y-position.y-size.y*0.5f, 0.0f),
                 size,
                 rotate,
                 glm::vec3(colour.x, colour.y, colour.z));
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, getTexture(name));
  draw();
}

void GraphicsHandler::draw() {

  glBindVertexArray(quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}


void GraphicsHandler::transformModel(glm::vec3 position, glm::vec2 size, GLfloat rotation, glm::vec3 colour) {
  glm::mat4 model;
  model = glm::translate(model, position);

  if ((int)rotation%360 != 0) {
    model = glm::translate(model, glm::vec3(0.5f*size.x, 0.5f*size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f*size.x, -0.5f*size.y, 0.0f));
  }

  model = glm::scale(model, glm::vec3(size, 1.0f));

  glUniformMatrix4fv(glGetUniformLocation(getShader(crntShader), (const GLchar*)"model"), 1, GL_FALSE, glm::value_ptr(model));
  glUniform3f(glGetUniformLocation(getShader(crntShader), "fragColour"), colour.x, colour.y, colour.z);
}

GLuint GraphicsHandler::getShader(std::string name) {
  if(shaders[name] == 0) {
    std::string err = "Attempting to use shader \"" + name + "\" that doesn't exist!";
    throw std::runtime_error(err);
  }
  return shaders[name];
}

GLuint GraphicsHandler::getTexture(std::string name) {
  if(textures[name] == 0) {
    std::string err = "Attempting to use texture \"" + name + "\" that doesn't exist!";
    //throw std::runtime_error(err);
  }
  return textures[name];
}

void GraphicsHandler::removeShader(std::string name) {
  if(shaders[name] == 0) {
    std::cout << "Attempting to remove \"" + name + "\" shader failed. It doesn't exist\n";
  }
  shaders.erase(name);
}

void GraphicsHandler::removeTexture(std::string name) {
  if(textures[name] == 0) {
    std::cout << "Attempting to remove \"" + name + "\" texture failed. It doesn't exist\n";
  }
  textures.erase(name);
}

void GraphicsHandler::loadTexture(std::string name, const char * filename){
  if(textures[name] != 0) {
    std::string err = "Error texture name \"" + name + "\" has already been used";
    throw std::runtime_error(err);
  }
  textures[name] = txt::LoadTexture(filename);
}

void GraphicsHandler::loadShaders(const char * vertex_file_path,const char * fragment_file_path, std::string name){
  
  if(shaders[name] != 0) {
    std::string err = "Error creating shader, the name \"" + name + "\" has already been used";
    throw std::runtime_error(err); 
  }
  
  // Create the shaders
  GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  std::cout << "Here";
  // Read the Vertex Shader code from the file
  std::string VertexShaderCode;
  std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
  if(VertexShaderStream.is_open()){
    std::string Line = "";
    while(getline(VertexShaderStream, Line))
      VertexShaderCode += "\n" + Line;
    VertexShaderStream.close();
  }else{
    printf("Impossible to open %s. \n", vertex_file_path);
    getchar();
    return;
  }

  // Read the Fragment Shader code from the file
  std::string FragmentShaderCode;
  std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
  if(FragmentShaderStream.is_open()){
    std::string Line = "";
    while(getline(FragmentShaderStream, Line))
      FragmentShaderCode += "\n" + Line;
    FragmentShaderStream.close();
  }

  GLint Result = GL_FALSE;
  int InfoLogLength;

  // Compile Vertex Shader
  printf("Compiling shader : %s\n", vertex_file_path);
  char const * VertexSourcePointer = VertexShaderCode.c_str();
  glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
  glCompileShader(VertexShaderID);

  // Check Vertex Shader
  glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if ( InfoLogLength > 0 ){
    std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    printf("%s\n", &VertexShaderErrorMessage[0]);
  }

  // Compile Fragment Shader
  printf("Compiling shader : %s\n", fragment_file_path);
  char const * FragmentSourcePointer = FragmentShaderCode.c_str();
  glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
  glCompileShader(FragmentShaderID);

  // Check Fragment Shader
  glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if ( InfoLogLength > 0 ){
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    printf("%s\n", &FragmentShaderErrorMessage[0]);
  }

  // Link the program
  printf("Linking program\n");
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, VertexShaderID);
  glAttachShader(ProgramID, FragmentShaderID);
  glLinkProgram(ProgramID);

  // Check the program
  glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if ( InfoLogLength > 0 ){
    std::vector<char> ProgramErrorMessage(InfoLogLength+1);
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    printf("%s\n", &ProgramErrorMessage[0]);
  }

  glDetachShader(ProgramID, VertexShaderID);
  glDetachShader(ProgramID, FragmentShaderID);

  glDeleteShader(VertexShaderID);
  glDeleteShader(FragmentShaderID);

  shaders[name] = ProgramID;
}

