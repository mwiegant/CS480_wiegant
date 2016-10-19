#include "object.h"

//Object::Object(char* objectName)
//{
//  // Set object name
//  name = objectName;
//
//  // Set angles and their divisors
//  spinAngle = 0.0f;
//  orbitAngle = 0.0f;
//  spinAngleDivisor = 2000;
//  orbitAngleDivisor = 2000;
//
//  // Set initial vector values for the axis of spin and the orbit
//  spinAxisVector = glm::vec3(0.0, 1.0, 0.0);
//  orbitVector = glm::vec3(5.0, 0.0, 0.0);
//
//  // Set flags for spinning and orbiting
//  spinEnabled = true;
//  orbitEnabled = true;
//
//  // Set spin and orbit directions
//  spinDirection = 1;
//  orbitDirection = 1;
//
//}

Object::Object(glm::vec3 _orbitVector)
{

  // these things get updated from the config file
  name = (char*) "planet";
  spinAxisVector = glm::vec3(0.0, 1.0, 0.0);
  orbitVector = _orbitVector;

  // these things always have their value
  spinAngle = 0.0f;
  orbitAngle = 0.0f;
  spinAngleDivisor = 4000;
  orbitAngleDivisor = 4000;

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

bool Object::Initialize()
{
  modelFilePath = (char*) "models/sphere.obj";
  textureFilePath = (char*) "textures/granite.jpg";

//  if(!ReadConfig())
//  {
//    std::printf("failed to load model from path: %s", modelFilePath);
//    return false;
//  }

  InitializeTexture();

  if(!InitializeModel())
  {
    std::printf("failed to load model from path: %s", modelFilePath);
    return false;
  }

  // initialize all satellites that this object may have
  for( int i = 0; i < satellites.size(); i++ )
  {
    if(!satellites[i]->Initialize())
    {
      std::printf("Model failed to Initialize\n");
      return false;
    }

  }

  return true;
}


void Object::Update(unsigned int dt, glm::mat4 systemModel)
{
  // update angles of rotation
  updateAngles(dt);

  // draw the object
  drawObject(systemModel);

  // call update on each of the children
  for( int i = 0; i < satellites.size(); i++ )
  {
    satellites[i]->Update(dt, model );
  }

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
void Object::drawObject(glm::mat4 systemModel)
{
  model = glm::rotate(systemModel, (orbitAngle), spinAxisVector);
  model = glm::translate(model, orbitVector);
  model *= glm::rotate(glm::mat4(1.0f), (spinAngle), spinAxisVector);
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

/*
 * For adding Objects that rotate around this object
 */
void Object::AddSatellite(Object* satellite)
{
  satellites.push_back( satellite );
}


/*
 * Reads in the configuration file that has data for this object.
 */
bool Object::ReadConfig()
{

  //TODO: render texture


  // todo

  return true;
}


bool Object::InitializeTexture()
{
  //initalize image loading with magick++
  Magick::Image* texture = new Magick::Image(textureFilePath);
  Magick::Blob m_blob;
  texture->write(&m_blob,"RGBA");

  //initialze textures
  glGenTextures(1, &aTexture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, aTexture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->columns(), texture->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  return true;
}

/*
 * Does all the model loading, including loading vertices and indices.
 */
bool Object::InitializeModel()
{
  Assimp::Importer importer;
  const aiScene *myScene = importer.ReadFile( modelFilePath, aiProcess_Triangulate);

  aiMesh* meshOne = myScene->mMeshes[0];

  aiVector3D aiVector;
  aiVector3D aiUV;
  unsigned int index;



  // load the models and the vertices
  for( int i = 0; i < meshOne->mNumFaces; i++ )
  {
    const aiFace& thisFace = meshOne->mFaces[i];

    for( int j = 0; j < 3; j++ )
    {

      //get the indices
      index = thisFace.mIndices[j];
      Indices.push_back( index );

      //get the vertices
      aiVector = meshOne->mVertices[thisFace.mIndices[j]];
      aiUV = meshOne->mTextureCoords[0][thisFace.mIndices[j]];

      Vertex *temp = new Vertex(glm::vec3(aiVector.x, aiVector.y, aiVector.z), glm::vec2(aiUV.x, aiUV.y));
      Vertices.push_back( *temp );

    }

  }


  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

  return true;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,uv));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, aTexture);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}























