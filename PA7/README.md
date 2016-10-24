# PA6: The Solar System

# Coding Team

```
Matt Monzon - the texture loading guy
Max Wiegant - the rendering guy 
Jayden Wang - the file loader
```

# Extra Credit Components

```
- (2pts) Live adjustment of simulation speed
- (2pts) Configuration file
- (4pts) Proper rings on other planets (total of 2) 
```

# Supported Interactions

## Keyboard

### General Program Controls

```
Q             -- Quit the program.
SPACEBAR      -- Pause or unpause all objects in the solar system
```

### Camera Controls

``` 
Z             -- Zoom the camera out
X             -- Zoom the camera in
UP-ARROW      -- Move the camera focus upwards
DOWN-ARROW    -- Move the camera focus downwards
LEFT-ARROW    -- Move the camera focus to the left
RIGHT-ARROW   -- Move the camera focus to the right
```

# Dependencies, Building, and Running

Please refer to the wiki for information on [installing dependencies](https://github.com/mwiegant/CS480_wiegant/wiki/General-Setup-Instructions).

## Building and Running
This project has both a cmake and a makefile, but only the cmake is maintained.

To build this project, first navigate to **CS480_wiegant/PA7**.

Next, run the following commands:
```bash
mkdir build
cd build
cmake ..
make
./Tutorial
```
