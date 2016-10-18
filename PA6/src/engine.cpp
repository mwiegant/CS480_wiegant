
#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;

  // set which object has keyboard focus, by default
  focusedObject = (char*) "planet";
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
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
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
    // adjust which part of solar system to render / focus on
    // -----------------------------------------------

/*
    // handle 1 - change focus to solar system
    if( m_event.key.keysym.sym == SDLK_1 )
      planetarySystem = SOLAR_SYSTEM;

    // handle 2 - change focus to mercury system
    else if( m_event.key.keysym.sym == SDLK_2 )
      planetarySystem = MERCURY_SYSTEM;

    // handle 3 - change focus to venus system
    else if( m_event.key.keysym.sym == SDLK_3 )
      planetarySystem = VENUS_SYSTEM;

    // handle 4 - change focus to earth system
    else if( m_event.key.keysym.sym == SDLK_4 )
      planetarySystem = EARTH_SYSTEM;

    // handle 5 - change focus to mars system
    else if( m_event.key.keysym.sym == SDLK_5 )
      planetarySystem = MARS_SYSTEM;

    // handle 6 - change focus to jupiter system
    else if( m_event.key.keysym.sym == SDLK_6 )
      planetarySystem = JUPITER_SYSTEM;

    // handle 7 - change focus to saturn system
    else if( m_event.key.keysym.sym == SDLK_7 )
      planetarySystem = SATURN_SYSTEM;

    // handle 8 - change focus to uranus system
    else if( m_event.key.keysym.sym == SDLK_8 )
      planetarySystem = URANUS_SYSTEM;

    // handle 9 - change focus to neptune system
    else if( m_event.key.keysym.sym == SDLK_9 )
      planetarySystem = NEPTUNE_SYSTEM;
*/

    // -----------------------------------------------
    // other keyboard event handling
    // -----------------------------------------------

    // todo - re-implement object focus
/*
    // handle w - toggle cube spin
    else if( m_event.key.keysym.sym == SDLK_w )
    {
      m_graphics->toggleObjectSpin(focusedObject);
    }
    // handle e - switch cube spin direction
    else if( m_event.key.keysym.sym == SDLK_e )
    {
      m_graphics->invertObjectSpin(focusedObject);
    }
    // handle s - toggle cube orbital rotation
    else if( m_event.key.keysym.sym == SDLK_s )
    {
      m_graphics->toggleObjectOrbit(focusedObject);
    }
    // handle d - switch cube orbital rotation direction
    else if( m_event.key.keysym.sym == SDLK_d )
    {
      m_graphics->invertObjectOrbit(focusedObject);
    }
*/
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
