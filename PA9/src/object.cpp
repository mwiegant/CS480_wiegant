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

}

Object::Object()
{

}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

bool Object::Initialize()
{
  modelFilePath = "models/Uranus.obj";
  textureFilePath = "textures/granite.jpg";

  //InitializeTexture();

  if(!InitializeModel())
  {
    std::printf("failed to load model from path: %s", modelFilePath.c_str());
    return false;
  }

  return true;
}

bool Object::Initialize(const char* fileName)
{
  modelFilePath = fileName;
  textureFilePath = "textures/granite.jpg";

  //InitializeTexture();

  if(!InitializeModel())
  {
    std::printf("failed to load model from path: %s", modelFilePath.c_str());
    return false;
  }

  return true;
}


void Object::Update(glm::mat4 systemModel)
{
  model = systemModel;
}


glm::mat4 Object::GetModel()
{
  return model;
}

bool Object::InitializeTexture()
{
  //initalize image loading with magick++
  Magick::Image* texture = new Magick::Image(textureFilePath.c_str());
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

  const aiScene *myScene = importer.ReadFile( modelFilePath.c_str(), aiProcess_Triangulate);

  aiMesh* meshOne = myScene->mMeshes[0];

  aiVector3D aiVector;

  //aiVector3D aiUV;

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

      //aiUV = meshOne->mTextureCoords[0][thisFace.mIndices[j]];

      /*Vertex *temp = new Vertex(glm::vec3(aiVector.x, aiVector.y, aiVector.z), glm::vec2(aiUV.x, aiUV.y));*/

      Vertex *temp = new Vertex(glm::vec3(aiVector.x, aiVector.y, aiVector.z), glm::vec3(30,30,30));

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
  //glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
  //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

/*
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, aTexture);
*/

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  //glDisableVertexAttribArray(2);
}























