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
//    Object(char* objectName); // todo - depricate this constructor
    Object(glm::vec3 _orbitVector);
    ~Object();
    void Update(unsigned int dt, glm::mat4 systemModel);
    void Render();

    bool Initialize();

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
    char* configFilePath;
    char* modelFilePath;
    char* textureFilePath;
};

#endif /* OBJECT_H */
