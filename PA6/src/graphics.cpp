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
  if(!InitializeObjects())
  {
    printf("Failed to Initialize objects\n");
  }

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

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER, "shaders/fragmentShader.glsl"))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

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
  glm::mat4 model = glm::mat4(1.0f);

  if(moveObjects)
  {
    // Update the sun, which will update all other objects
    Sun->Update(dt, model);
  }

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
  for(int i = 0; i < masterList.size(); i++)
  {
    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr( masterList[i]->GetModel() ));
    masterList[i]->Render();
  }

  // Render the object
//  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr( masterList[1]->GetModel() ));
//  masterList[1]->Render();


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

void Graphics::SlowDownSystem()
{
  // todo
}

void Graphics::SpeedUpSystem()
{
  // todo
}

void Graphics::ToggleObjectMovement()
{
  moveObjects = bool ( moveObjects ? 0 : 1 );
}

bool Graphics::InitializeObjects()
{
  // Create the sun
  Sun = new Object( glm::vec3(0.0, 0.0, 0.0) );

  // Create planetary objects
  Object* Mercury = new Object( glm::vec3(2.0, 0.0, 0.0) );
  Object* Venus = new Object( glm::vec3(8.0, 0.0, 0.0) );
  Object* Earth = new Object( glm::vec3(16.0, 0.0, 0.0) );
  Object* Moon = new Object( glm::vec3(2.0, 0.0, 0.0) );
  Object* Mars = new Object( glm::vec3(20.0, 0.0, 0.0) );
  Object* Jupiter = new Object( glm::vec3(30.0, 0.0, 0.0) );
  Object* Europa = new Object( glm::vec3(1.0, 0.0, 0.0) );
  Object* Ganymede = new Object( glm::vec3(2.0, 0.0, 0.0) );
  Object* Castillo = new Object( glm::vec3(1.5, 0.0, 0.0) );
  Object* Io = new Object( glm::vec3(4.0, 0.0, 0.0) );
  Object* Saturn = new Object( glm::vec3(45.0, 0.0, 0.0) );
  Object* Titan = new Object( glm::vec3(2.0, 0.0, 0.0) );
  Object* Enceladus = new Object( glm::vec3(5.0, 0.0, 0.0) );
  Object* Uranus = new Object( glm::vec3(67.0, 0.0, 0.0) );
  Object* Titania = new Object( glm::vec3(1.0, 0.0, 0.0) );
  Object* Neptune = new Object( glm::vec3(80.0, 0.0, 0.0) );
  Object* Triton = new Object( glm::vec3(1.0, 0.0, 0.0) );
  Object* Pluto = new Object( glm::vec3(105.0, 0.0, 0.0) );


  // All objects that will be rendered must be added to this list
  masterList.push_back( Sun );
  masterList.push_back( Mercury );
  masterList.push_back( Venus );
  masterList.push_back( Earth );
  masterList.push_back( Moon );
  masterList.push_back( Mars );
  masterList.push_back( Jupiter );
  masterList.push_back( Europa );
  masterList.push_back( Ganymede );
  masterList.push_back( Castillo );
  masterList.push_back( Io );
  masterList.push_back( Saturn );
  masterList.push_back( Titan );
  masterList.push_back( Enceladus );
  masterList.push_back( Uranus );
  masterList.push_back( Titania );
  masterList.push_back( Neptune );
  masterList.push_back( Triton );
  masterList.push_back( Pluto );

  // Add planets as satellites
  Sun->AddSatellite( Mercury );
  Sun->AddSatellite( Venus );
  Sun->AddSatellite( Earth );
  Sun->AddSatellite( Mars );
  Sun->AddSatellite( Jupiter );
  Sun->AddSatellite( Saturn );
  Sun->AddSatellite( Uranus );
  Sun->AddSatellite( Neptune );
  Sun->AddSatellite( Pluto );

  // Add moons as satellites
  Earth->AddSatellite( Moon );
  Jupiter->AddSatellite( Europa );
  Jupiter->AddSatellite( Ganymede );
  Jupiter->AddSatellite( Castillo );
  Jupiter->AddSatellite( Io );
  Saturn->AddSatellite( Titan );
  Saturn->AddSatellite( Enceladus );
  Uranus->AddSatellite( Titania );
  Neptune->AddSatellite( Triton );

  // initialize all the objects
  if(!Sun->Initialize())
  {
    printf("Solar System failed to Initialize\n");
    return false;
  }

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

