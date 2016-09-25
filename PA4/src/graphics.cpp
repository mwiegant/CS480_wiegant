#include "graphics.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

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

  // Create the object
  objects.push_back( new Object((char *) "planet") );
  objects.push_back( new Object((char *) "moon") );

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

  return true;
}

/*
 * Stop or start the cube from spinning on its axis
 */
bool Graphics::toggleObjectSpin(char* objectName)
{
  for( int i = 0; i < objects.size(); i++ )
  {
    if( strncmp(objects[i]->GetName(), objectName, strlen(objectName)) == 0 )
    {
      objects[i]->ToggleSpin();

      return true;
    }
  }

  return false;
}

/*
 * Change the direction that the cube is spinning in
 */
bool Graphics::invertObjectSpin(char* objectName)
{
  for( int i = 0; i < objects.size(); i++ )
  {
    if( strncmp(objects[i]->GetName(), objectName, strlen(objectName)) == 0 )
    {
      objects[i]->InvertSpinDirection();

      return true;
    }
  }

  return false;
}

/*
 * Stop or start the cube from rotating in 3d space
 */
bool Graphics::toggleObjectOrbit(char* objectName)
{
  for( int i = 0; i < objects.size(); i++ )
  {
    if( strncmp(objects[i]->GetName(), objectName, strlen(objectName)) == 0 )
    {
      objects[i]->ToggleOrbit();

      return true;
    }
  }

  return false;
}

/*
 * Change the direction that the cube is rotating in
 */
bool Graphics::invertObjectOrbit(char* objectName)
{
  for( int i = 0; i < objects.size(); i++ )
  {
    if( strncmp(objects[i]->GetName(), objectName, strlen(objectName)) == 0 )
    {
      objects[i]->InvertOrbitDirection();

      return true;
    }
  }

  return false;
}


void Graphics::Update(unsigned int dt)
{
  glm::mat4 model = glm::mat4(1.0f);

  /*
   * The planet doesn't really need model passed to it, but the
   * moon definitely does, and since they're the same class I'm going
   * to have to just do things this way
   */

  // planet update
  objects[0]->Update( dt, model );

  // update model with the model from the planet
  model = objects[0]->GetModel();

  // moon update
  objects[1]->Update( dt, model );
}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Set wireframe mode
//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

  // Render the object
  for( int i = 0; i < objects.size(); i++ )
  {
    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr( objects[i]->GetModel() ));
    objects[i]->Render();
  }

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
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

