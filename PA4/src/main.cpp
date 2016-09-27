#include <iostream>

#include "engine.h"

// todo - add logic to check for arguments, like --help or -s <filename>

int main(int argc, char **argv)
{

  if(argc < 2)
  {
    printf("No model filepath was provided.\n");
    printf("Usage: ./Tutorial path/to/file\n");
    return 1;
  }


  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Max Wiegant -- Computer Graphics", 800, 600);
  if(!engine->Initialize( argv[1] ))
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }
  engine->Run();
  delete engine;
  engine = NULL;
  return 0;
}
