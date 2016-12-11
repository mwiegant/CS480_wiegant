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
  eyePosition = glm::vec3(20.0f, 25.0f, -15.0f);
  focusPoint = glm::vec3(-13.0f, 0.0f, 0.0f);
  yAxis = glm::vec3(0.0f, 1.0f, 0.0f); // we do not change this vector

  //--Init the view and projection matrices
  //  if you will be having a moving camera the view matrix will need to more dynamic
  //  ...Like you should update it before you render more dynamic 
  //  for this project having them static will be fine
  view = glm::lookAt( eyePosition, //Eye Position
                      focusPoint, //Focus point
                      yAxis); //Positive Y is up

  projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                 float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                 0.01f, //Distance to the near plane, normally a small value like this
                                 110.0f); //Distance to the far plane,

  // for looking up at the scoreboard
  lookUp = false;

  // the hard-coded position of the scoreboard
  scoreboardPosition = glm::vec3(-20.0f, 20.0f, 0.0f);

  // the modifier that will be used to get back-and-forth from the scoreboardPositin
  // (dividing by -30 is intentional)
  focusPointModifier = scoreboardPosition / (float) maxMoves;

  moveNumber = 0;

  return true;
}

glm::mat4 Camera::GetProjection()
{
  return projection;
}

glm::mat4 Camera::GetView()
{
  // factor in movement to-and-from the scoreboard
  UpdateView();

  return view;
}

void Camera::ToggleLookUp(bool lookUp)
{
  this->lookUp = lookUp;
}

void Camera::UpdateView()
{
  // if looking up, and haven't finished the movement to look up
  if( lookUp && moveNumber < maxMoves )
  {
    focusPoint += focusPointModifier;

    moveNumber++;
  }
  // else, if looking down, and haven't finished the movement to look down
  else if( !lookUp && moveNumber > 0)
  {
    focusPoint += -focusPointModifier;

    moveNumber--;
  }

  // re-calculate the view
  view = glm::lookAt( eyePosition, //Eye Position
                      focusPoint, //Focus point
                      yAxis); //Positive Y is up
}





