# cobalt
A 3D general-purpose game engine for Unix distributions, being used in the game Celestine.

## System Requirements
To compile and run you need the following:
- A GPU with **OpenGL 4.0** minimum support;
- **GCC** and [**GLFW 3**](https://stackoverflow.com/questions/17768008/how-to-build-install-glfw-3-and-use-it-in-a-linux-project) installed on your machine.
- **FreeType** library. Install it from their [website](https://freetype.org/)
- **CMake 3.10**

## Build
Use the provided build scripts to build the tests and example.

```
chmod +x build_example.sh 
./build_example.sh
```

## Compatibility
Currently only compatible with **Linux** distributions. There are future plans for a **Windows** version. Mostly untested outside of **Ubuntu 23.10**.

## Engine structure
**cobalt** is divided into two main parts:
- [**core**](https://github.com/teoemeaesse/cobalt-engine/tree/main/cobalt/core) - Core engine library functionality, heavily dependent on GLFW for graphics.
- [**engine**](https://github.com/teoemeaesse/cobalt-engine/tree/main/cobalt/engine) - **cobalt** engine code, composed from independent modules that use the [**core**](https://github.com/teoemeaesse/cobalt-engine/tree/main/cobalt/core) library.
- **editor** (future) - A game level editor is planned for after the base engine development is done.