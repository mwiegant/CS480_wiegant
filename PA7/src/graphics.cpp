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
  systemSpeedModifier = 1.0f;

  return true;
}

void Graphics::Update(unsigned int dt)
{
  glm::mat4 model = glm::mat4(1.0f);

  if(moveObjects)
  {
    float speedCoeff = 1;
    float newPos;

    newPos = dt * speedCoeff;


    // Update the sun, which will update all other objects
    Sun->Update(newPos, systemSpeedModifier, model);
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

bool Graphics::LookUp()
{
  return m_camera->LookUp();
}

bool Graphics::LookDown()
{
  return m_camera->LookDown();
}

bool Graphics::LookLeft()
{
  return m_camera->LookLeft();
}

bool Graphics::LookRight()
{
  return m_camera->LookRight();
}

void Graphics::SpeedUpSystem()
{
  systemSpeedModifier *= 1.25;
}

void Graphics::SlowDownSystem()
{
  systemSpeedModifier *= 0.75;
}

void Graphics::ToggleObjectMovement()
{
  moveObjects = bool ( moveObjects ? 0 : 1 );
}

void Graphics::ToggleChairMode()
{
  Sun->ToggleChairMode();
}

bool Graphics::InitializeObjects()
{
  // Create the sun
  Sun = new Object();

  // Create planetary objects
  Object* Mercury = new Object();
  Object* Venus = new Object();
  Object* Earth = new Object();
  Object* Moon = new Object();
  Object* Mars = new Object();
  Object* Jupiter = new Object();
  Object* Europa = new Object();
  Object* Ganymede = new Object();
  Object* Castillo = new Object();
  Object* Io = new Object();
  Object* Saturn = new Object();
  Object* Titan = new Object();
  Object* Enceladus = new Object();
  Object* Uranus = new Object();
  Object* Titania = new Object();
  Object* Neptune = new Object();
  Object* Triton = new Object();
  Object* Pluto = new Object();


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

  // Read in the objects information from the config file
  if(!readInAll())
  {
   printf("Failed to read in from config file!\n");
  }

  // initialize all the objects
  if(!Sun->Initialize())
  {
    printf("Solar System failed to Initialize\n");
    return false;
  }

  return true;
}

bool Graphics::readInAll()
{
  ifstream fileIn;
  int i;

  fileIn.clear();
  fileIn.open( "config/solar_system.cnf" );
  

  if( !fileIn.good() )
  {
    printf("File not good!\n");
    return false;
  }


  //ignore up to the name of the Sun
  fileIn.ignore( 256, ':' );

  for( i = 0; i < masterList.size(); i++ )
  {
    masterList[i]->ReadConfig( fileIn );
  }

  fileIn.close();

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

