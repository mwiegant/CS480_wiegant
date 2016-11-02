#ifndef SHADER_H
#define SHADER_H

#include <vector>
#include <string>
#include <fstream>

#include "graphics_headers.h"

class Shader
{
  public:
    Shader();
    ~Shader();
    bool Initialize();
    void Enable();
    bool AddShader(GLenum ShaderType, std::string ShaderFilename);
    bool Finalize();
    GLint GetUniformLocation(const char* pUniformName);
  private:
    bool LoadShader(std::string shaderFilename, std::string& shaderData);
    GLuint m_shaderProg;    
    std::vector<GLuint> m_shaderObjList;
};

#endif  /* SHADER_H */
