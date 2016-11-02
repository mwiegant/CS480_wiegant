/**
 * @file shader.h
 *
 * @brief Definition file for shader class
 * 
 * @author Cactus Coolers
 * 
 * @details Specifies all methods and variables for shader class
 *
 * @version 1.00
 *
 * @Note None
 */

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
