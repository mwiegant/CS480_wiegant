#include <iostream>
#include <string>

#include "engine.h"

// todo - add logic to check for arguments, like --help or -s <filename>

int main(int argc, char **argv)
{
  std::string filename;

  if( argc < 2 )
  {
    cout << "Error - please pass filepath to the model after the executable name" << endl;
    return -1;
  }

//  filename = argv[2];

  //todo - remove after we finish testing
  std::cout << "ADIOS MOTHER FUCKER!!!!" << std::endl;

  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Max Wiegant -- Computer Graphics", 800, 600);
  if(!engine->Initialize("omg this is a filename"))
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
