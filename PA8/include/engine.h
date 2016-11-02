/**
 * @file engine.h
 *
 * @brief Definition file for engine class
 * 
 * @author Cactus Coolers
 * 
 * @details Specifies all methods and variables for engine class
 *
 * @version 1.00
 *
 * @Note None
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <sys/time.h>
#include <assert.h>

#include "window.h"
#include "graphics.h"
#include "graphics_headers.h"

class Engine
{
  public:
    Engine(string name, int width, int height);
    Engine(string name);
    ~Engine();
    bool Initialize();
    void Run();
    void Keyboard();
    void Mouse();
    unsigned int getDT();
    long long GetCurrentTimeMillis();
  
  private:
    // Window related variables
    Window *m_window;    
    string m_WINDOW_NAME;
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    bool m_FULLSCREEN;
    SDL_Event m_event;

    // Graphics related variables
    Graphics *m_graphics;
    unsigned int m_DT;
    long long m_currentTimeMillis;
    bool m_running;

    // todo - re purpose this variable for solar system project
    // For determining which object keyboard input should affect
    char* focusedObject;

    // For specifying path to the model
    char* modelPath;
};

#endif // ENGINE_H
