# PA0: Triangle

# Dependencies, Building, and Running

Please refer to the wiki for information on [installing dependencies](https://github.com/mwiegant/CS480_wiegant/wiki/General-Setup-Instructions).

## Building and Running
To build this project there are two options. One is to use CMake which makes including new libraries easier, and handles new files added automatically to the src and include directory. CMake is a small new learning curve but makes things easier in the future.
The second option is to use the provided Makefile which is used as usual.

Running the make in a separate directory will allow easy cleanup of the build data, and an easy way to prevent unnecessary data to be added to the git repository.  

### CMake Instructions

```bash
mkdir build
cd build
cmake ..
make
./Tutorial
```

### Makefile Instructions 

```bash
mkdir build
cd build
cp ../makefile .
make
./Tutorial
```

