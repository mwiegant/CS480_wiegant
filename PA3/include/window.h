#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
//#include <SDL/SDL_ttf.h>

#include <string>
using namespace std;

class Window
{
  public:
    Window();
    ~Window();
    bool Initialize(const string &name, int* width, int* height);
    void Swap();


  private:
    SDL_Window* gWindow;
    SDL_GLContext gContext;
};

#endif /* WINDOW_H */
