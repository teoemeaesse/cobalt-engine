# CMake minimum version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(cobalt)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCEDIR cobalt)
set(INCLUDEDIR include)
set(LIBDIR lib)

if(TEST_ENVIRONMENT)
  add_definitions(-DTEST_ENVIRONMENT)
endif()

find_package(Doxygen)

if(DOXYGEN_FOUND)
  # Define the Doxygen target
  add_custom_target(
    doc_doxygen
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM)
endif()

# Conditional flags based on build type
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG -DGL_GLEXT_PROTOTYPES"
  )# Set release flags to optimize and remove debug info
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DGL_GLEXT_PROTOTYPES") # Debug
                                                                     # flags
endif()

# Set the build directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/include)

# Include directories
include_directories(${SOURCEDIR})
include_directories(${INCLUDEDIR})

# Recursively collect all .cpp files in the core and test directories
file(GLOB_RECURSE CB_SOURCES ${SOURCEDIR}/*.cpp)

# Add the GLFW and GLEW dependencies
set(GLFW_BUILD_DOCS
    OFF
    CACHE BOOL "" FORCE)
add_subdirectory(${LIBDIR}/glfw)
add_subdirectory(${LIBDIR}/glew/build/cmake)

# Create an executable for the example
add_executable(cobalt ${CB_SOURCES})

# Set the output directory
set_target_properties(cobalt PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                        ${EXECUTABLE_OUTPUT_PATH})

target_include_directories(cobalt PRIVATE ${SOURCEDIR} ${LIBDIR}/glew/include)

target_precompile_headers(cobalt PRIVATE ${SOURCEDIR}/core/pch.h)

if(APPLE)
  target_link_libraries(
    cobalt
    PRIVATE glfw
            glew
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreVideo"
            pthread
            dl
            m)
elseif(UNIX AND NOT APPLE)
  target_link_libraries(
    cobalt
    PRIVATE GL
            GLU
            glfw
            glew
            X11
            Xxf86vm
            Xrandr
            pthread
            Xi
            dl
            m
            Xinerama
            Xcursor)
endif()
