#include "graphics.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{
  // todo - deallocate space for objects vector
}

bool Graphics::Initialize(int width, int height)
{
  // Used for the linux OS
  #if !defined(__APPLE__) && !defined(MACOSX)
    // cout << glewGetString(GLEW_VERSION) << endl;
    glewExperimental = GL_TRUE;

    auto status = glewInit();

    // This is here to grab the error that comes from glew init.
    // This error is an GL_INVALID_ENUM that has no effects on the performance
    glGetError();

    //Check for error
    if (status != GLEW_OK)
    {
      std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
      return false;
    }
  #endif

  // For OpenGL 3
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  // Set up the objects
  //if(!InitializeObjects())
  //{
   // printf("Failed to Initialize objects\n");
  //}

  // Set up the physics world
  physicsWorld.Initialize();
  InitializeObjects();

  // Set up the shaders
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader(GL_VERTEX_SHADER, "shaders/vertexShader.glsl"))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Load different fragment shaders on MAC machines
#if defined(__APPLE__) || defined(MACOSX)

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER, "shaders/fragmentShader_mac.glsl"))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

#else //linux as default

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER, "shaders/fragmentShader.glsl"))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }
#endif

  // Connect the program
  if(!m_shader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // enable object movement
  moveObjects = true;

  return true;
}

void Graphics::Update(unsigned int dt)
{
  physicsWorld.Update(dt);
}


void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));

  // Render all objects in the master list
  for(int i = 0; i < physicsWorld.objectList.size(); i++)
  {
    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr( physicsWorld.objectList[i]->GetModel() ));
    physicsWorld.objectList[i]->Render();
  }

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

bool Graphics::ZoomIn()
{
  return m_camera->ZoomIn();
}

bool Graphics::ZoomOut()
{
  return m_camera->ZoomOut();
}

bool Graphics::LookLeft()
{
  return m_camera->LookLeft();
}

bool Graphics::LookRight()
{
  return m_camera->LookRight();
}

bool Graphics::InitializeObjects()
{
  // add objects to the physics world
  //physicsWorld.AddFloor();

  /*physicsWorld.AddFrontFacingWall( btVector3(0.0f, 0.0f, 6.0f) );
  physicsWorld.AddFrontFacingWall( btVector3(0.0f, 0.0f, -6.0f) );

  physicsWorld.AddSideFacingWall( btVector3(6.0f, 0.0f, 0.0f) );
  physicsWorld.AddSideFacingWall( btVector3(-6.0f, 0.0f, 0.0f) );

  physicsWorld.AddCube( btVector3(0,0,0) );
  physicsWorld.AddCube( btVector3(1,0,3.6) );
  physicsWorld.AddCube( btVector3(3.6,0,1.0) );
  physicsWorld.AddCube( btVector3(0,0,0) );
  physicsWorld.AddCube( btVector3(0,0,0) );
  physicsWorld.AddCube( btVector3(5,0,5) );
  physicsWorld.AddCube( btVector3(5,0,-5) );
  physicsWorld.AddCylinder( btVector3(1,0,1) );
  physicsWorld.AddCylinder( btVector3(4,0,1) );
  physicsWorld.AddCylinder( btVector3(1,0,4) );
  physicsWorld.AddSphere( btVector3(1,0,1) );
*/
   physicsWorld.AddTriMeshShape(btVector3(0,0,0));
   physicsWorld.AddSphere( btVector3(0,10,0.9) );
   physicsWorld.AddSphere( btVector3(0,10,0.9) );
   physicsWorld.AddSphere( btVector3(0,10,0.9) );
   physicsWorld.AddSphere( btVector3(0,10,0.9) );
  // physicsWorld.AddSphere( btVector3(5.9,20,3.9) );
  // physicsWorld.AddSphere( btVector3(2.7,80,-3.9f) );
  // physicsWorld.AddSphere( btVector3(1.7,60,0.5f) );
  // physicsWorld.AddSphere( btVector3(2.7,180,3.9f) );
  // physicsWorld.AddSphere( btVector3(1,59,1) );

  return true;
}

std::string Graphics::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}
