# PA3: Planet with Moon



# Supported Interactions

## Keyboard

### General Program Controls
```
Q -- Quit the program.
1 -- Set focus on the planet
2 -- Set focus on the moon
```

### Cube Controls
The controls below will affect whichever planet currently has **focus**.

For example, if the moon has **focus**, pressing **S** will stop it from
orbitting.

``` 
W -- Toggle the cube to stop or start spinning on it's axis
E -- Invert the direction the cube is spinning in
S -- Toggle the cube to stop or start orbiting
D -- Invert the direction the cube is orbiting in
```

## Mouse

Click anywhere on the screen to toggle the currently focused cube to start or stop orbiting.

# Dependencies, Building, and Running

Please refer to the wiki for information on [installing dependencies](https://github.com/mwiegant/CS480_wiegant/wiki/General-Setup-Instructions).

## Building and Running
This project has both a cmake and a makefile, but only the cmake is maintained.

To build this project, first navigate to **CS480_wiegant/PA3**.

Next, run the following commands:
```bash
mkdir build
cd build
cmake ..
make
./Tutorial
```
