#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <vector>
#include <string>

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "physicsWorld.h"
#include "catapult.h"

using namespace std;

class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();

    // todo - repurpose this function
    void LaunchBall();

    // for updating the catapult arm
    void AdjustCatapultArm(bool moveForward, bool enableMovement);

    // for updating the view
    void LookLeft();
    void LookRight();

    // For adjusting the lighting
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

    // GL locations for lighting variables
    GLint lightPos;
    GLint eyePos;
    GLint ambientProd;
    GLint diffuseProd;
    GLint specularProd;

    // values to be used for lighting variables
    float ambientVal;
    float diffuseVal;
    float specularVal;

    Catapult* catapult;
    PhysicsWorld physicsWorld;
};

#endif /* GRAPHICS_H */
