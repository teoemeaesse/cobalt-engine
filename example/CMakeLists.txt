# CMake minimum version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(cobalt-example)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(SOURCEDIR ../cobalt)
set(INCLUDEDIR ../include)
set(EXAMPLEDIR .)

# Set additional flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DGL_GLEXT_PROTOTYPES")

# Set the build directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/include)

# Include directories
include_directories(${SOURCEDIR})
include_directories(${INCLUDEDIR})
include_directories(${EXAMPLEDIR}/src)

# Recursively collect all .cpp files in the core, engine and test directories
file(GLOB_RECURSE EXAMPLE_SOURCES ${EXAMPLEDIR}/src/*.cpp)
file(GLOB_RECURSE CB_SOURCES ${SOURCEDIR}/core/*.cpp ${SOURCEDIR}/engine/*.cpp)

# Create an executable for the example
add_executable(example-app ${EXAMPLE_SOURCES} ${CB_SOURCES})

# Set the output directory
set_target_properties(example-app PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

# Find the Freetype library
find_package(Freetype REQUIRED)

target_include_directories(example-app PRIVATE
    ${SOURCEDIR}
)
target_link_libraries(example-app PRIVATE
    GL
    GLU
    glfw3
    X11
    Xxf86vm
    Xrandr
    pthread
    Xi
    dl
    m
    Xinerama
    Xcursor
    ${FREETYPE_LIBRARIES}
)