# CMake minimum version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(cobalt-core-tests)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(SOURCEDIR ../cobalt)
set(INCLUDEDIR ../include)
set(LIBDIR ../lib)
set(TESTDIR .)

if(TEST_ENVIRONMENT)
  add_definitions(-DTEST_ENVIRONMENT)
endif()

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

# Create a static library for the core
add_library(cobalt_core STATIC ${CORE_SOURCES})
target_precompile_headers(cobalt_core PRIVATE ${SOURCEDIR}/core/core.h)
target_include_directories(cobalt_core PUBLIC ${SOURCEDIR} ${LIBDIR}/glew/include ${LIBDIR}/glfw/include)

# Add the GLFW and GLEW dependencies
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
add_subdirectory(${LIBDIR}/glfw glfw_build)
add_subdirectory(${LIBDIR}/glew/build/cmake glew_build)

# Include the Unity test framework
add_library(unity STATIC ${INCLUDEDIR}/unity/unity.c)

# Create an executable for each test source file
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
    target_precompile_headers(${TEST_NAME} PRIVATE
        ${SOURCEDIR}/core/core.h
    )
    if(APPLE)
        target_link_libraries(${TEST_NAME} PRIVATE
            cobalt_core
            glfw
            glew
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreVideo"
            pthread
            dl
            m
            unity
        )
    elseif(UNIX AND NOT APPLE)
        target_link_libraries(${TEST_NAME} PRIVATE
            cobalt_core
            GL
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
            Xcursor
            unity
        )
    endif()
    
    # Run the tests after building
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

    # Remove the executable after running the tests
    set_tests_properties(${TEST_NAME} PROPERTIES POST_TEST
        COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE:${TEST_NAME}>
    )
endforeach()