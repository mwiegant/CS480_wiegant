#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

bool Camera::Initialize(int w, int h)
{
  // Initialize vectors that will be changed during runtime
  eyePosition = glm::vec3(0.0, 6.5, -50.0);
  focusPoint = glm::vec3(0.0, 0.0, -2.0);

  //--Init the view and projection matrices
  //  if you will be having a moving camera the view matrix will need to more dynamic
  //  ...Like you should update it before you render more dynamic 
  //  for this project having them static will be fine
  view = glm::lookAt( eyePosition, //Eye Position
                      focusPoint, //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                 float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                 0.01f, //Distance to the near plane, normally a small value like this
                                 300.0f); //Distance to the far plane,
  return true;
}

glm::mat4 Camera::GetProjection()
{
  return projection;
}

glm::mat4 Camera::GetView()
{
  return view;
}

/*
 * Moves the eye position in
 */
bool Camera::ZoomIn()
{
  // check if the user is too close to keep zooming in
  if( eyePosition.z == -1.0 )
  {
    return false;
  }

  eyePosition += glm::vec3(0.0, 0.0, 1.0);

  view = glm::lookAt( eyePosition, //Eye Position
                      focusPoint, //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  return true;
}

/*
 * Moves the eye position out
 */
bool Camera::ZoomOut()
{
  eyePosition += glm::vec3(0.0, 0.0, -1.0);

  view = glm::lookAt( eyePosition, //Eye Position
                      focusPoint, //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  return true;
}

/*
 * Adjusts the focus point up
 */
bool Camera::LookUp()
{
  focusPoint += glm::vec3(0.0, 0.0, 1.0);

  view = glm::lookAt( eyePosition, //Eye Position
                      focusPoint, //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  return true;
}

/*
 * Adjusts the focus point down
 */
bool Camera::LookDown()
{
  focusPoint += glm::vec3(0.0, 0.0, -1.0);

  view = glm::lookAt( eyePosition, //Eye Position
                      focusPoint, //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  return true;
}

/*
 * Adjusts the focus point left
 */
bool Camera::LookLeft()
{
  focusPoint += glm::vec3(0.75, 0.25, 0.0);

  view = glm::lookAt( eyePosition, //Eye Position
                      focusPoint, //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  return true;
}

/*
 * Adjusts the focus point right
 */
bool Camera::LookRight()
{
  focusPoint += glm::vec3(-0.75, -0.25, 0.0);

  view = glm::lookAt( eyePosition, //Eye Position
                      focusPoint, //Focus point
                      glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

  return true;
}







