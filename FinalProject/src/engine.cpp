#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window();
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }


  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

    // Check keyboard input and mouse events
    while(SDL_PollEvent(&m_event) != 0)
    {
      Keyboard();
      Mouse();
    }

    // Update and render the graphics
    m_graphics->Update(m_DT);
    m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::Keyboard()
{
  bool lookUp = false;

  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }

  /* key press events */
  else if (m_event.type == SDL_KEYDOWN)
  {

    // -----------------------------------------------
    // handle escape - end program
    // -----------------------------------------------
    if( m_event.key.keysym.sym == SDLK_ESCAPE )
    {
      m_running = false;
    }

    // -----------------------------------------------
    // Adjust the catapult arm to move
    // -----------------------------------------------

    /* move the arm forward */
    else if( m_event.key.keysym.sym == SDLK_UP )
    {
      // bool moveForward, bool enableMovement
      m_graphics->AdjustCatapultArm(true, true);
    }

    /* move the arm back */
    else if( m_event.key.keysym.sym == SDLK_DOWN )
    {
      // bool moveForward, bool enableMovement
      m_graphics->AdjustCatapultArm(false, true);
    }

    // -----------------------------------------------
    // launch the ball from the catapult arm
    // -----------------------------------------------
    else if( m_event.key.keysym.sym == SDLK_SPACE )
    {
      m_graphics->LaunchBall();
    }

    // -----------------------------------------------
    // move the catapult
    // -----------------------------------------------
    else if( m_event.key.keysym.sym == SDLK_w )
    {
      m_graphics->moveCatapult(1);
    }

    else if( m_event.key.keysym.sym == SDLK_s)
    {
      m_graphics->moveCatapult(2);
    }

    else if( m_event.key.keysym.sym == SDLK_a )
    {
      m_graphics->moveCatapult(3);
    }

    else if( m_event.key.keysym.sym == SDLK_d)
    {
      m_graphics->moveCatapult(4);
    }

    // -----------------------------------------------
    // change the lighting effects
    // -----------------------------------------------
    else if( m_event.key.keysym.sym == SDLK_EQUALS )
    {
      m_graphics->ambientChange(1);
    }

    else if( m_event.key.keysym.sym == SDLK_MINUS )
    {
      m_graphics->ambientChange(-1);
    }

    else if( m_event.key.keysym.sym == SDLK_p)
    {
      m_graphics->diffuseChange(1);
    }

    else if( m_event.key.keysym.sym == SDLK_o )
    {
      m_graphics->diffuseChange(-1);
    }

    else if( m_event.key.keysym.sym == SDLK_PERIOD )
    {
      m_graphics->specularChange(1);
    }

    else if( m_event.key.keysym.sym == SDLK_COMMA )
    {
      m_graphics->specularChange(-1);
    }

  }

  /* key release events */
  else if (m_event.type == SDL_KEYUP)
  {

    // -----------------------------------------------
    // Adjust the catapult arm to stop moving
    // -----------------------------------------------

    /* move the arm forward */
    if( m_event.key.keysym.sym == SDLK_UP )
    {
      // bool moveForward, bool enableMovement
      m_graphics->AdjustCatapultArm(true, false);
    }

      /* move the arm back */
    else if( m_event.key.keysym.sym == SDLK_DOWN )
    {
      // bool moveForward, bool enableMovement
      m_graphics->AdjustCatapultArm(false, false);
    }
  }

}

void Engine::Mouse()
{
  // catch a mouse down event
  if( m_event.type == SDL_MOUSEBUTTONDOWN )
  {

/*
    if( m_event.button.button == SDL_BUTTON_LEFT )
    {
      m_graphics->toggleObjectOrbit(focusedObject);
    }
*/

  }
}


unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
