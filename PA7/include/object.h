#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <iostream>
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
    bool Initialize();
    void Update(unsigned int dt, float speedModifier, glm::mat4 systemModel);
    void Render();
    glm::mat4 GetModel();

    void AddSatellite(Object* satellite);
    void ToggleChairMode();

    //function to read in the required parts from the config file
    bool ReadConfig(std::ifstream& fileIn);

  private:

    bool InitializeTexture();
    bool InitializeModel(bool chairMode);

    // Update functions
    void updateAngles(float dt);
    void drawObject(glm::mat4 matrix);

    glm::mat4 model;

    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    //Texture
    GLuint aTexture;

    // Unique Identifier
    char* name;

    // Path names
    char* modelFilePath;
    char* textureFilePath;
    char* chairFilePath;

    bool chairMode;

    // Spin variables
    float spinAngle;
    float spinSpeed;
    int spinAngleDivisor;
    bool spinEnabled;
    int spinDirection;
    glm::vec3 spinAxisVector;

    // Orbit variables
    float orbitAngle;
    float orbitSpeed;
    int orbitAngleDivisor;
    bool orbitEnabled;
    int orbitDirection;
    glm::vec3 orbitVector;

    // For objects that orbit around this object
    std::vector<Object *> satellites;
};

#endif /* OBJECT_H */
