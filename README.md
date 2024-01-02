[![C/C++ CI](https://github.com/teoemeaesse/cobalt-engine/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/teoemeaesse/cobalt-engine/actions/workflows/c-cpp.yml)
# cobalt
A 3D general-purpose game engine for Unix distributions, being used in the game Celestine.

## System Requirements
To compile and run you need the following:
- A GPU with **OpenGL 4.1** minimum support;
- **CMake 3.10**

## Build
Use the provided build scripts to build the tests and editor.

```
./setup.sh
./build_editor.sh
```

## Tests
You can run the provided script on your machine or use the Docker image.

```
sudo docker build -t cobalt-tests .
sudo docker run cobalt-tests
```

## Compatibility
Currently compatible with **Linux** distributions and **MacOS** on ARM. There are future plans for a **Windows** version. Mostly untested outside of **Ubuntu 23.10** and **MacOS Sonoma 14.1**.

## Engine structure
**cobalt** is divided into two main parts:
- [**core**](https://github.com/teoemeaesse/cobalt-engine/tree/main/cobalt/core) - Core engine library functionality, heavily dependent on GLFW for graphics.
- [**engine**](https://github.com/teoemeaesse/cobalt-engine/tree/main/cobalt/engine) - **cobalt** engine code, composed from independent modules that use the [**core**](https://github.com/teoemeaesse/cobalt-engine/tree/main/cobalt/core) library.
- [**editor**](https://github.com/teoemeaesse/cobalt-engine/tree/main/cobalt/editor) A game level editor is in development.