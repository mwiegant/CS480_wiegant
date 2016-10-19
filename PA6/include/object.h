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
    char* GetName();

    // User Input Control Functions
    void ToggleSpin();
    void ToggleOrbit();
    void InvertSpinDirection();
    void InvertOrbitDirection();

    void AddSatellite(Object* satellite);

  private:

    bool ReadConfig();
    bool InitializeTexture();
    bool InitializeModel();

    // Update functions
    void updateAngles(unsigned int dt);
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
    char* configFilePath;
    char* modelFilePath;
    char* textureFilePath;

    // Spin variables
    float spinAngle;
    int spinAngleDivisor;
    bool spinEnabled;
    int spinDirection;
    glm::vec3 spinAxisVector;

    // Orbit variables
    float orbitAngle;
    int orbitAngleDivisor;
    bool orbitEnabled;
    int orbitDirection;
    glm::vec3 orbitVector;

    // For objects that orbit around this object
    std::vector<Object *> satellites;
};

#endif /* OBJECT_H */
