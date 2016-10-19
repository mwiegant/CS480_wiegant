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

    // for updating the view
    bool ZoomIn();
    bool ZoomOut();
    bool LookLeft();
    bool LookRight();

    // for adjusting speed or movement of the system
    void SpeedUpSystem();
    void SlowDownSystem();
    void ToggleObjectMovement();

  private:

    bool InitializeObjects();
    bool readInAll();

    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    // System movement variables
    float systemSpeedModifier;
    bool moveObjects;

    char* modelPath;
    Object* Sun;
    vector<Object *> masterList;
};

#endif /* GRAPHICS_H */
