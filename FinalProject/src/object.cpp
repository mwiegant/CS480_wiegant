
#include "object.h"
#include <iostream>


Object::Object()
{
  triangleMesh = NULL;
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}


/*
 * Loads the models and textures that are used by an object.
 *
 * The model loading also sets up a triangleMesh that can be used by Bullet.
 */
bool Object::Initialize(const char* modelPath, const char* texturePath)
{
  modelFilePath = modelPath;
  textureFilePath = texturePath;

  triangleMesh = new btTriangleMesh();

  if(!InitializeModel())
  {
    std::printf("failed to load model from path: %s\n", modelFilePath.c_str());
    return false;
  }

  if(!InitializeTexture())
  {
    std::printf("failed to load texture from path: %s\n", textureFilePath.c_str());
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

btTriangleMesh* Object::GetTriangleMesh()
{
  if(triangleMesh == NULL)
  {
    printf("Error - whoa! Something is wrong, the triangle mesh is NULL for some reason....\n");
  }

  return triangleMesh;
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
 * For use with loading complex models
 */
bool Object::InitializeModel()
{
  unsigned int index;
  aiMesh* meshOne;
  aiVector3D aiUV;
  aiVector3D aiVector;
  aiVector3D* aiNormal;
  Assimp::Importer importer;
  btVector3 triArray[3];

//  printf("reading in model from filepath: %s\n", modelFilePath.c_str());

  // attempt to read the model from file
  try
  {
    const aiScene *myScene = importer.ReadFile( modelFilePath.c_str(), aiProcess_Triangulate);
    meshOne = myScene->mMeshes[0];
  }
  catch (int Exception)
  {
    return false;
  }

//  printf("read in the file successfully\n");

  //get the normals
  aiNormal = meshOne -> mNormals;

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

      //load triArray vertices for triMesh
      triArray[j] = btVector3(aiVector.x, aiVector.y, aiVector.z);

      Vertex *temp = new Vertex(glm::vec3(aiVector.x, aiVector.y, aiVector.z), glm::vec2(aiUV.x, aiUV.y), glm::vec3(aiNormal[thisFace.mIndices[j]].x, aiNormal[thisFace.mIndices[j]].y, aiNormal[thisFace.mIndices[j]].z));

      Vertices.push_back( *temp );
    }

    // add face to triMesh
    triangleMesh->addTriangle(triArray[0], triArray[1], triArray[2]);
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
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,uv));
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,normal));

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, aTexture);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}





