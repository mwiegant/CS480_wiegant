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

    // Setters


  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    // Unique Identifier
    std::string objName;

    // Drawing variables
    float angle;
    bool shouldSpin;
    bool shouldOrbit;
    bool invertSpin;
    bool invertOrbit;
    glm::vec3 spinAxisVector;
    glm::vec3 orbitVector;
};

#endif /* OBJECT_H */
