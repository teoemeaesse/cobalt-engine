# CMake minimum version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(cobalt-core-tests)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(SOURCEDIR ../cobalt)
set(INCLUDEDIR ../include)
set(TESTDIR .)

# Set additional flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DGL_GLEXT_PROTOTYPES")

# Set the build directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/include)

# Enable testing
enable_testing()
include(CTest)

# Include directories
include_directories(${SOURCEDIR})
include_directories(${INCLUDEDIR})
include_directories(${TESTDIR}/core)

# Recursively collect all .cpp files in the core and test directories
file(GLOB_RECURSE TEST_SOURCES ${TESTDIR}/core/*.cpp)
file(GLOB_RECURSE CORE_SOURCES ${SOURCEDIR}/core/*.cpp)

# Include the Unity test framework
add_library(unity STATIC ${INCLUDEDIR}/unity/unity.c)

# Find the Freetype library
find_package(Freetype REQUIRED)

# Create an executable for each test source file
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE} ${CORE_SOURCES})
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
    target_include_directories(${TEST_NAME} PRIVATE
        ${SOURCEDIR}
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
        ${FREETYPE_LIBRARIES}
    )
    
    # Run the tests after building
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

    # Remove the executable after running the tests
    set_tests_properties(${TEST_NAME} PROPERTIES POST_TEST
        COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE:${TEST_NAME}>
    )
endforeach()