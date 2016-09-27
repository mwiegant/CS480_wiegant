#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>
#include <fstream>
#include "graphics_headers.h"

// todo - remove when done testing
#include <iostream>

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt, glm::mat4 systemModel);
    void Render();

    // Getters
    glm::mat4 GetModel();

    // Import model
    bool LoadModel(char* filename);

  private:

    glm::mat4 model;

    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

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
