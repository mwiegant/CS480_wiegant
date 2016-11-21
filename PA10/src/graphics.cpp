#include "graphics.h"

Graphics::Graphics()
{
  ambientVal = 0.1f;
  diffuseVal = 0.1f;
  specularVal = 0.1f;
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
  m_projectionMatrix = m_shader->GetUniformLocation("Projection");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("View");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("Model");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  // Locate the light position in the shader
  lightPos = m_shader -> GetUniformLocation("LightPosition");
  if (ambientProd == INVALID_UNIFORM_LOCATION) 
  {
    printf("LightPosition not found\n");
    return false;
  }

  // Locate the ambient product in the shader
  ambientProd = m_shader -> GetUniformLocation("AmbientProduct");
  if (ambientProd == INVALID_UNIFORM_LOCATION) 
  {
    printf("AmbientProduct not found\n");
    return false;
  }

  // Locate the diffuse product in the shader
  diffuseProd = m_shader -> GetUniformLocation("DiffuseProduct");
  if (diffuseProd == INVALID_UNIFORM_LOCATION) 
  {
    printf("DiffuseProduct not found\n");
    return false;
  }

  // Locate the specular product in the shader
  specularProd = m_shader -> GetUniformLocation("SpecularProduct");
  if (specularProd == INVALID_UNIFORM_LOCATION) 
  {
    printf("SpecularProduct not found\n");
    return false;
  }

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // pinball variable initialization
  gameState = GAME_STATE_READY;
  ballsLeft = 3;

  //enable lighting??
  glEnable(GL_LIGHTING);

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

  // Send in the lighting values to the shader
  glUniform4f(ambientProd, ambientVal, ambientVal, ambientVal, 2.0f);
  glUniform4f(diffuseProd, diffuseVal, diffuseVal, diffuseVal, diffuseVal);
  glUniform4f(specularProd, specularVal, specularVal, specularVal, 0.1f);

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

/*
 * Launches the pinball ball if the game is in the correct state to launch the ball.
 */
void Graphics::LaunchBall()
{
  if( gameState == GAME_STATE_READY)
  {
    physicsWorld.setPinballVelocity(btVector3(-50.0f, 0.0f, 0.0f) );

    gameState = GAME_STATE_PLAYING;
  }
}

void Graphics::ToggleLookUp(bool lookUp)
{
  m_camera->ToggleLookUp(lookUp);
}

bool Graphics::InitializeObjects()
{
  /*
   * Objects we need:
   *  - pinball board
   *  - pinball ball
   *  - flippers (2)
   *
   *
   *  Objects we may need:
   *  - cylindrical bumpers (2?)
   *  - plunger (we can probably do without this)
   */


  /// Pinball Board
  /* position, weight, modelPath, texturePath */
  physicsWorld.AddTriMeshShape( btVector3(0.0f, 0.0f, 0.0f), btScalar(0.0f),
                                "models/Board_Base.obj", "textures/Base_Tex.jpg");

  /// Paddles
  /* position, paddleIdentifier, mass, modelPath, texturePath */
  physicsWorld.AddPaddle( btVector3(0.0f, 0.0f, 0.0f), "paddle_left", btScalar(1.0f),
                          "models/Paddle_Left.obj", "textures/granite.jpg" );

  physicsWorld.AddPaddle( btVector3(0.0f, 0.0f, 0.0f), "paddle_right", btScalar(1.0f),
                          "models/Paddle_Right.obj", "textures/granite.jpg" );

  /// Pinball ball
  /* position, half-size vectors, weight, modelPath, texturePath */
  physicsWorld.AddPinball( btVector3(0.0f, 0.0f, 0.0f), btScalar(1.0f), btScalar(1.0f),
                           "models/sphere.obj", "textures/Neptune.jpg" );


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

void Graphics::ambientChange(int change)
{
  if( change > 0 )
  {
    if( ambientVal < 1.0f )
    {
      ambientVal += 0.01f;
    }
  }
  else if( change < 0 )
  {
    if( ambientVal > 0 )
    {
      ambientVal -= 0.01f;
    }
  }
}

void Graphics::diffuseChange(int change)
{
  if( change > 0 )
  {
    if( diffuseVal < 1.0f )
    {
      diffuseVal += 0.01f;
    }
  }
  else if( change < 0 )
  {
    if( diffuseVal > 0 )
    {
      diffuseVal -= 0.01f;
    }
  }
}

void Graphics::specularChange(int change)
{
  if( change > 0 )
  {
    if( specularVal < 1.0f )
    {
      specularVal += 0.01f;
    }
  }
  else if( change < 0 )
  {
    if( specularVal > 0 )
    {
      specularVal -= 0.01f;
    }
  }
}















