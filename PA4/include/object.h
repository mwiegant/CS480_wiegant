#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <fstream>
#include <string>
#include "graphics_headers.h"

#include <iostream>

class Object
{
  public:
    Object();
    ~Object();
    bool Initialize(char* modelPath);
    void Update(unsigned int dt);
    void Render();

    glm::mat4 GetModel();

  private:
    bool loadModel(char* filepath);


    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float angle;
};

#endif /* OBJECT_H */
