
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

bool Engine::Initialize(const char* modelPath)
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
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, modelPath))
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
    // handle escape - end program
    if( m_event.key.keysym.sym == SDLK_ESCAPE )
    {
      m_running = false;
    }
    // handle 1 - change focus to planet
    if( m_event.key.keysym.sym == SDLK_1 )
    {
      focusedObject = (char*) "planet";
    }
    // handle 2 - change focus to moon
    if( m_event.key.keysym.sym == SDLK_2 )
    {
      focusedObject = (char*) "moon";
    }
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
  }
}

void Engine::Mouse()
{
  // catch a mouse down event
  if( m_event.type == SDL_MOUSEBUTTONDOWN )
  {

    if( m_event.button.button == SDL_BUTTON_LEFT )
    {
      m_graphics->toggleObjectOrbit(focusedObject);
    }
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
