#include "object.h"

Object::Object()
{

  // Set default variables (updated by config file)
  name = (char*) "planet";
  spinAxisVector = glm::vec3(0.0, 1.0, 0.0);
  orbitVector = glm::vec3( 1.0, 0.0, 0.0 );

  spinAngle = 0.0f;
  orbitAngle = 0.0f;
  spinAngleDivisor = 4000;
  orbitAngleDivisor = 4000;

  // Set flags for spinning and orbiting
  spinEnabled = true;
  orbitEnabled = true;

  // Set spin and orbit directions and speed
  spinDirection = 1;
  orbitDirection = 1;

  spinSpeed = 0;
  orbitSpeed = 0;

  // allocate size to private data members
  name = new char[ 30 ];
  modelFilePath = new char[ 30 ];
  textureFilePath = new char[ 30 ];
  chairFilePath = new char[ 30 ];

  // set path to the chair model
  chairMode = false;
  std::strcpy(chairFilePath, "models/chair.obj");

}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

bool Object::Initialize()
{
  InitializeTexture();

  // initialize model without chair mode on
  if(!InitializeModel(false))
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


void Object::Update(unsigned int dt, float speedModifier, glm::mat4 systemModel)
{
  // update angles of rotation
  updateAngles( dt * speedModifier );

  // draw the object
  drawObject(systemModel);

  // call update on each of the children
  for( int i = 0; i < satellites.size(); i++ )
  {
    satellites[i]->Update(dt, speedModifier, model );
  }

}

/*
 * Renders/draws object onto screen
 */
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

/*
 * For use during graphics rendering
 */
glm::mat4 Object::GetModel()
{
  return model;
}

/*
 * For adding Objects that rotate around this object
 */
void Object::AddSatellite(Object* satellite)
{
  satellites.push_back( satellite );
}

/*
 * Toggles chair mode. Either reloads all the models as chairs,
 * or all the models as their respective planet or moon
 */
void Object::ToggleChairMode()
{
  chairMode = !chairMode;

  Vertices.clear();
  Indices.clear();

  // re-initialize the model on this planet
  if( !InitializeModel(chairMode) )
  {
    printf("WARNING - There may have been an issue toggling chair mode.");
  }

  // re-initialize the model on all satellites
  for( int i = 0; i < satellites.size(); i++ )
  {
    satellites[i]->ToggleChairMode();
  }
}

/*
 * Reads in the configuration file that has data for this object.
 */
bool Object::ReadConfig(std::ifstream& fileIn)
{
  std::string dummy;
  char cdummy;
  float fdumone;
  float fdumtwo;
  float fdumthr;

  //read in the name to a dummy string - the file is already there
  fileIn >> dummy;
  std::strcpy( name, dummy.c_str() );

  //ignore to the model path then read it in
  fileIn.ignore( 256, ':' );
  fileIn >> dummy;
  std::strcpy( modelFilePath, dummy.c_str() );

  //ignore to the texture path then read it in
  fileIn.ignore( 256, ':' );
  fileIn >> dummy;
  std::strcpy( textureFilePath, dummy.c_str() );

  //ignore to the orbit axis
  fileIn.ignore( 256, ':' );
  fileIn >> fdumone >> cdummy >> fdumtwo >> cdummy >> fdumthr;
  orbitVector = glm::vec3( fdumone, fdumtwo, fdumthr );

  //ignore to the orbit speed
  fileIn.ignore( 256, ':' );
  fileIn >> orbitSpeed;

  //ignore to the rotation axis
  fileIn.ignore( 256, ':' );
  fileIn >> fdumone >> cdummy >> fdumtwo >> cdummy >> fdumthr;
  spinAxisVector = glm::vec3( fdumone, fdumtwo, fdumthr );

  //ignore to the rotation speed
  fileIn.ignore( 256, ':' );
  fileIn >> spinSpeed;

  //ignore to the name of the next object
  fileIn.ignore( 254, ':' );

  return true;
}

/*
 * Does all the texture loading
 */
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

  //read texture data into active gl texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->columns(), texture->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());

  //set texture parameters/format
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  return true;
}

/*
 * Does all the model loading, including loading vertices and indices.
 *
 * Supports an extra mode to load chair models instead of the model
 * specified from the configuration file.
 */
bool Object::InitializeModel(bool chairMode)
{
  Assimp::Importer importer;
  aiMesh* meshOne;
  aiVector3D aiVector;
  aiVector3D aiUV;
  unsigned int index;

  // decide which file to read in from
  if( chairMode )
  {
    const aiScene *myScene = importer.ReadFile( chairFilePath, aiProcess_Triangulate);
    meshOne = myScene->mMeshes[0];
  } else {
    const aiScene *myScene = importer.ReadFile( modelFilePath, aiProcess_Triangulate);
    meshOne = myScene->mMeshes[0];
  }

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

/*
 * Angle adjustment component of update process
 */
void Object::updateAngles(float dt)
{
  float spinAdjustment, orbitAdjustment;

  spinAdjustment = float (( dt * M_PI * spinSpeed ) / 5000 );
  orbitAdjustment = float (( dt * M_PI * orbitSpeed ) / 5000 );

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






















