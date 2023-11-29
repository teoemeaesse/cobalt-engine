# CMake minimum version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(Cobalt)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(SOURCEDIR src)
set(LIBDIR lib)
set(TESTDIR test)

# Set additional flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DGL_GLEXT_PROTOTYPES")

# Set the build directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Enable testing
enable_testing()
include(CTest)

# Include directories
include_directories(${SOURCEDIR})
include_directories(${LIBDIR})
include_directories(${TESTDIR})

# Recursively collect all .cpp files in the src/ directory and its subdirectories
file(GLOB_RECURSE SOURCES ${SOURCEDIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${SOURCEDIR}/*.h)
file(GLOB_RECURSE TEST_SOURCES ${TESTDIR}/*.cpp)
file(GLOB_RECURSE ENGINE ${SOURCEDIR}/*.cpp)

# Include the Unity test framework
add_library(unity STATIC lib/unity.c)

# Add executable
# add_executable(cobalt ${SOURCES})

# Create an executable for each test source file
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE} ${ENGINE})
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
    target_include_directories(${TEST_NAME} PRIVATE
        ${SOURCEDIR}
        /usr/local/include/freetype2
    )
    target_link_libraries(${TEST_NAME} PRIVATE
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
        freetype
        unity
    )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DGL_GLEXT_PROTOTYPES")
    
    # Run the tests after building
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

    # Remove the executable after running the tests
    set_tests_properties(${TEST_NAME} PROPERTIES POST_TEST
        COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE:${TEST_NAME}>
    )
endforeach()