#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>
#include <cstdio>
#include "graphics_headers.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>
#include <Magick++.h>

class Object
{
  public:
    Object();
    ~Object();
    void Update(glm::mat4 systemModel);
    void Render();

    bool Initialize();
    bool Initialize(const char* modelPath, const char* texturePath);

    // Getters
    glm::mat4 GetModel();

  private:

    bool InitializeTexture();
    bool InitializeModel();

    glm::mat4 model;

    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    //Texture
    GLuint aTexture;

    // Path names
    std::string configFilePath;
    std::string modelFilePath;
    std::string textureFilePath;
};

#endif /* OBJECT_H */
