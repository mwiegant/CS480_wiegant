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
#include "physicsWorld.h"

class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();

    void LaunchBall();

    // todo - update or depricate some of these
    // for updating the view
    void ToggleLookUp(bool lookUp);
    void LookLeft();
    void LookRight();

    void ambientChange(int change);
    void diffuseChange(int change);
    void specularChange(int change);

  private:
    bool InitializeObjects();

    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    // pinball specific variables
    int gameState;
    int ballsLeft;

    // GL locations for lighting variables
    GLint lightPos;
    GLint ambientProd;
    GLint diffuseProd;
    GLint specularProd;

    // values to be used for lighting variables
    float ambientVal;
    float diffuseVal;
    float specularVal;

    bool moveObjects;

    vector<Object *> masterList;

    PhysicsWorld physicsWorld;
};

#endif /* GRAPHICS_H */
