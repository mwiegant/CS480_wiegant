#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt);
    void Render();

    // Getters
    glm::mat4 GetModel();

    // User Input Control Functions
    void ToggleSpin();
    void ToggleOrbit();
    void InvertSpinDirection();
    void InvertOrbitDirection();

  private:
    void updateAngles(unsigned int dt);
    void drawCube();

    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    // Spin variables
    float spinAngle;
    bool spinEnabled;
    bool spinClockwise;
    glm::vec3 spinAxisVector;

    // Orbit variables
    float orbitAngle;
    bool orbitEnabled;
    bool orbitClockwise;
    glm::vec3 orbitVector;
};

#endif /* OBJECT_H */
