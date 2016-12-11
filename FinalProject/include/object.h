#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>
#include <cstdio>
#include "graphics_headers.h"

#include <btBulletDynamicsCommon.h>

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

    /*  NOTE - MATT - LOOK HERE!!
     *
     *  we have 2 initialize functions right now, and 2 initializeModel functions.
     *
     *  lets just always pass a btTriangleMesh to the initializeModel (so get rid of the
     *  one that doesn't have that parameter).
     *
     *  we will also want to create a function called getTriangleMesh() that retrieves the
     *  triangle mesh.
     *
     *  this will allow us to separate out the object code from the physicsworld code,
     *  right now they are just too closely coupled and its a fucking bitch to expand out the
     *  project while they are that closely related.
     *
     *  --------
     *
     *  I may begin implementing some of this stuff as I need to.
     */

    bool Initialize(const char* modelPath, const char* texturePath);

    // Getters
    glm::mat4 GetModel();
    btTriangleMesh* GetTriangleMesh();

  private:
    bool InitializeTexture();

    bool InitializeModel();

    glm::mat4 model;

    // For use with Bullet
    btTriangleMesh* triangleMesh;

    // Model variables
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    // Texture variables
    GLuint aTexture;

    // Path names
    std::string configFilePath;
    std::string modelFilePath;
    std::string textureFilePath;
};

#endif /* OBJECT_H */
