#include "object.h"

Object::Object(char* objectName)
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

//  Vertices = {
//    // {<position>}, {<color>}
//    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
//    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
//    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
//    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
//    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
//    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
//    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
//    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
//  };
//
//  Indices = {
//    2, 3, 4,
//    8, 7, 6,
//    1, 5, 6,
//    2, 6, 7,
//    7, 8, 4,
//    1, 4, 8,
//    1, 2, 4,
//    5, 8, 6,
//    2, 1, 6,
//    3, 2, 7,
//    3, 7, 4,
//    5, 1, 8
//  };

//  // The index works at a 0th index
//  for(unsigned int i = 0; i < Indices.size(); i++)
//  {
//    Indices[i] = Indices[i] - 1;
//  }
//
//  glGenBuffers(1, &VB);
//  glBindBuffer(GL_ARRAY_BUFFER, VB);
//  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
//
//  glGenBuffers(1, &IB);
//  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
//  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

  // Set object name
  name = objectName;

  // Set angles and their divisors
  spinAngle = 0.0f;
  orbitAngle = 0.0f;
  spinAngleDivisor = 2000;
  orbitAngleDivisor = 2000;

  // Set initial vector values for the axis of spin and the orbit
  spinAxisVector = glm::vec3(0.0, 1.0, 0.0);
  orbitVector = glm::vec3(5.0, 0.0, 0.0);

  // Set flags for spinning and orbiting
  spinEnabled = true;
  orbitEnabled = true;

  // Set spin and orbit directions
  spinDirection = 1;
  orbitDirection = 1;

}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

bool Object::Initialize(const char* _filePath)
{
  std::string filePath = "theFilepath";

  Assimp::Importer importer;
  const aiScene *myScene = importer.ReadFile( filePath.c_str(), aiProcess_Triangulate);

  glm::vec3 color = glm::vec3(0.5f, 0.2f, 0.0f);
  aiVector3D aiVector;
  unsigned int index;

//  Assimp::Importer

//  Assimp::aiMesh* theAiMesh = aiScene->mMeshes[0]

//   Assimp::aiVector3D aiVertices = myScene->mMeshes[0]->mVertices


  // {<position>}, {<color>}

  // SHOULD get all our vertices
//  for(int i = 0; i < myScene->mMeshes[0]->mVertices->Length(); i++ )
  for(int i = 0; i < myScene->mMeshes[0]->mNumVertices; i++ )
  {
    aiVector = myScene->mMeshes[0]->mVertices[i];

    Vertices.push_back( { glm::vec3(aiVector.x, aiVector.y, aiVector.z), color } );
  }

  // get indices
  for(int i = 0; i < myScene->mMeshes[0]->mNumFaces; i++ )
  {
    for(int j = 0; j < myScene->mMeshes[0]->mFaces[i].mNumIndices; j++)
    {
      index = myScene->mMeshes[0]->mFaces[i].mIndices[j];

      Indices.push_back( index - 1 );
    }
  }

  //  // The index works at a 0th index
//  for(unsigned int i = 0; i < Indices.size(); i++)
//  {
//    Indices[i] = Indices[i] - 1;
//  }
//
  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

  return true;
}


void Object::Update(unsigned int dt, glm::mat4 systemModel)
{
  // update angles of rotation
  updateAngles(dt);

  // draw the cube
  drawCube(systemModel);
}


/*
 * Angle adjustment component of update process
 */
void Object::updateAngles(unsigned int dt)
{
  float spinAdjustment, orbitAdjustment;

  spinAdjustment = float ( dt * M_PI / spinAngleDivisor );
  orbitAdjustment = float ( dt * M_PI/ orbitAngleDivisor );

  spinAdjustment *= ( (int) spinEnabled * spinDirection );
  orbitAdjustment *= ( (int) orbitEnabled * orbitDirection );

  spinAngle += spinAdjustment;
  orbitAngle += orbitAdjustment;
}


/*
 * Drawing component of update process
 */
void Object::drawCube(glm::mat4 systemModel)
{
  model = glm::rotate(systemModel, (orbitAngle), spinAxisVector);
  model = glm::translate(model, orbitVector);
  model *= glm::rotate(glm::mat4(1.0f), (spinAngle), spinAxisVector);

  // only scale the moon
  if( strncmp(name, "moon", 4) == 0)
  {
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
  }

}

glm::mat4 Object::GetModel()
{
  return model;
}

char* Object::GetName()
{
  return name;
}

void Object::ToggleSpin()
{
  spinEnabled = !spinEnabled;
}

void Object::ToggleOrbit()
{
  orbitEnabled = !orbitEnabled;
}

void Object::InvertSpinDirection()
{
  spinDirection *= -1;

  // if the cube isn't spinning, have it start spinning
  if(!spinEnabled)
    ToggleSpin();
}

void Object::InvertOrbitDirection()
{
  orbitDirection *= -1;

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

