#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"

class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();

    // methods for object interaction
    bool toggleObjectSpin(char* objectName);
    bool invertObjectSpin(char* objectName);
    bool toggleObjectOrbit(char* objectName);
    bool invertObjectOrbit(char* objectName);

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

//    Object *m_cube;
    vector<Object *> objects;
};

#endif /* GRAPHICS_H */
