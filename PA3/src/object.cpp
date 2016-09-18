#include "object.h"

Object::Object()
{  
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */

  Vertices = {
    // {<position>}, {<color>}
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  // Set angles and their divisors
  spinAngle = 0.0f;
  orbitAngle = 0.0f;
  spinAngleDivisor = 1200;
  orbitAngleDivisor = 1050;

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

  // Set initial vector values for the axis of spin and the orbit
  spinAxisVector = glm::vec3(0.0, 1.0, 0.0);
  orbitVector = glm::vec3(5.0, 0.0, 0.0);

  // Set flags for spinning and orbiting
  spinEnabled = true;
  orbitEnabled = true;

  // Set spin and orbit directions
  spinClockwise = true;
  orbitClockwise = true;

}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::Update(unsigned int dt)
{
  // update angles of rotation
  updateAngles(dt);

  // draw the cube
  drawCube();
}


/*
 * Angle adjustment component of update process
 */
void Object::updateAngles(unsigned int dt)
{
  // check if the cube is currently spinning
  if(spinEnabled)
  {

    // adjust the angle of rotation, according to spin direction
    if(spinClockwise)
    {
      spinAngle += dt * M_PI / spinAngleDivisor;

      // reset angle when it gets larger than a full rotation
      spinAngle = (spinAngle <= 360.0f) ? spinAngle : (spinAngle - 360.0f);
    }
    else
    {
      spinAngle -= dt * M_PI/ spinAngleDivisor;

      // reset angle to 360 when it gets to be less than 0
      spinAngle = (spinAngle >= 0.0f) ? spinAngle : (spinAngle + 360.0f);
    }
  }


  // check if the cube is currently orbiting
  if(orbitEnabled)
  {

    // adjust the angle of rotation, according to orbit direction
    if(orbitClockwise)
    {
      orbitAngle += dt * M_PI/ orbitAngleDivisor;

      // reset angle when it gets larger than a full rotation
      orbitAngle = (orbitAngle <= 360.0f) ? orbitAngle : (orbitAngle - 360.0f);
    }
    else
    {
      orbitAngle -= dt * M_PI/ orbitAngleDivisor;

      // reset angle to 360 when it gets to be less than 0
      orbitAngle = (orbitAngle >= 0.0f) ? orbitAngle : (orbitAngle + 360.0f);
    }
  }

}


/*
 * Drawing component of update process
 */
void Object::drawCube()
{
  model = glm::rotate(glm::mat4(1.0f), (orbitAngle), spinAxisVector);
  model = glm::translate(model, orbitVector);
  model *= glm::rotate(glm::mat4(1.0f), (spinAngle), spinAxisVector);
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::ToggleSpin()
{
  spinEnabled = (spinEnabled) ? false : true;
}

void Object::ToggleOrbit()
{
  orbitEnabled = (orbitEnabled) ? false : true;
}

void Object::InvertSpinDirection()
{
  spinClockwise = (spinClockwise) ? false : true;

  // if the cube isn't spinning, have it start spinning
  if(!spinEnabled)
    ToggleSpin();
}

void Object::InvertOrbitDirection()
{
  orbitClockwise = (orbitClockwise) ? false : true;

  // if the cube isn't orbiting, have it start orbiting
  if(!orbitEnabled)
    ToggleOrbit();
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

