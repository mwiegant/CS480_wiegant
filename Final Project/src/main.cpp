#include <cstdio>

#include <Magick++.h>

#include "engine.h"

int main(int argc, char **argv)
{

  // Start an engine
  Engine *engine = new Engine("Cactus Coolers -- Computer Graphics", 800, 650);

  Magick::InitializeMagick(*argv);

  // Initialize the engine
  if(!engine->Initialize())
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }

  // Run the engine, and clean it up after
  engine->Run();

  delete engine;
  engine = NULL;
  return 0;
}
