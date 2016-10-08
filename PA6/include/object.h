#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>
#include "graphics_headers.h"

//todo - remove after we finish testing
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>

class Object
{
  public:
    Object(char* objectName);
    ~Object();
    void Update(unsigned int dt, glm::mat4 systemModel);
    void Render();

    bool Initialize(const char* filePath);

    // Getters
    glm::mat4 GetModel();
    char* GetName();

    // User Input Control Functions
    void ToggleSpin();
    void ToggleOrbit();
    void InvertSpinDirection();
    void InvertOrbitDirection();

  private:
    void updateAngles(unsigned int dt);
    void drawCube(glm::mat4 matrix);

    glm::mat4 model;

    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    // Unique Identifier
    char* name;

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
};

#endif /* OBJECT_H */
