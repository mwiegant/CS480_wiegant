# PA2: Spinning Cube with Interactions

```
    Note - There is a known issue that occurs when the cube is both 
    spinning and orbiting. If the spin and orbit are in opposite
    directions, the cube appears to not be spinning. I was aware of
    a way to fix this but when I implemented this fix the issue did
    not go away. I will solve this problem in the future, since I 
    have not had time to fix this issue for this project. The 
    keyboard interactions otherwise work quite fantastically.
```

# Supported Interactions

## Keyboard

``` 
Q -- Quit the program.
W -- Toggle the cube to stop or start spinning on it's axis
E -- Invert the direction the cube is spinning in
S -- Toggle the cube to stop or start orbiting
D -- Invert the direction the cube is orbiting in
```

## Mouse

Click anywhere on the screen to toggle the cube to start or stop orbiting.

# Dependencies, Building, and Running

Please refer to the wiki for information on [installing dependencies](https://github.com/mwiegant/CS480_wiegant/wiki/General-Setup-Instructions).

## Building and Running
This project has both a cmake and a makefile, but only the cmake is maintained.

To build this project, first navigate to **CS480_wiegant/PA1**.

Next, run the following commands:
```bash
cd build
cmake ..
make
./Tutorial
```
