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

    void ToggleLookUp(bool lookUp);
  
  private:
    void UpdateView();


    // for looking up at the scoreboard
    bool lookUp;

    // the position of the scoreboard (hard-coded)
    glm::vec3 scoreboardPosition;

    // the movement vector to get back-and-forth from the scoreboardPosition
    glm::vec3 focusPointModifier;

    // for determining movement back-and-forth from the scoreboardPosition
    int moveNumber;
    const int maxMoves = 30;

    glm::vec3 eyePosition;
    glm::vec3 focusPoint;
    glm::vec3 yAxis;

    glm::mat4 projection;
    glm::mat4 view;
};

#endif /* CAMERA_H */
