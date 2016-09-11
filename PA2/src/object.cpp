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

  angle = 0.0f;

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

  // Default name
  objName = "cube";

  // Set initial vector values for the axis of spin and the orbit
  spinAxisVector = glm::vec3(0.0, 1.0, 0.0);
  orbitVector = glm::vec3(5.0, 0.0, 0.0);

  // Set flags for spinning and orbiting
  shouldSpin = true;
  shouldOrbit = true;

  // Set spin and orbit directions
  invertSpin = false;
  invertOrbit = false;

}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::Update(unsigned int dt)
{
  angle += dt * M_PI/1000;

  // reset angle when it gets larger than a full rotation
  if( angle > 360.0f )
    angle -= 360.0f;

  // check if spin and orbit should be inverted or not
  if( invertOrbit ) {
    orbitVector *= -1;
    invertOrbit = false;
  }

  if( invertSpin ) {
    spinAxisVector *= -1;
    invertSpin = false;
  }

  // draw the cube to the screen
  if(shouldOrbit | shouldSpin) {
    model = glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 1.0, 0.0));
  }

  // move the cube out to orbit
  if(shouldOrbit)
  {
    model = glm::translate(model, orbitVector);
  }

  // apply orbital rotation to cube
  if(shouldSpin)
  {
    model *= glm::rotate(glm::mat4(1.0f), (angle), spinAxisVector);
  }

}

glm::mat4 Object::GetModel()
{
  return model;
}

bool Object::isSpinning()
{
  return shouldSpin;
}

bool Object::isOrbiting()
{
  return shouldOrbit;
}

void Object::ToggleSpin()
{
  // invert the value of shouldSpin
  if(shouldSpin)
    shouldSpin = false;
  else
    shouldSpin = true;
}

void Object::ToggleOrbit()
{
  // invert the value of shouldOrbit
  if(shouldOrbit)
    shouldOrbit = false;
  else
    shouldOrbit = true;
}

void Object::InvertSpinDirection()
{
  spinAxisVector *= -1;
}

void Object::InvertOrbitDirection()
{
  orbitVector *= -1;
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

