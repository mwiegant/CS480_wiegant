/**
 * @file camera.h
 *
 * @brief Definition file for camera class
 * 
 * @author Cactus Coolers
 * 
 * @details Specifies all methods and variables for camera class
 *
 * @version 1.00
 *
 * @Note None
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"

class Camera
{
  public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    glm::mat4 GetProjection();
    glm::mat4 GetView();

    bool ZoomIn();
    bool ZoomOut();
    bool LookUp();
    bool LookDown();
    bool LookLeft();
    bool LookRight();
  
  private:
    glm::vec3 eyePosition;
    glm::vec3 focusPoint;

    glm::mat4 projection;
    glm::mat4 view;
};

#endif /* CAMERA_H */
