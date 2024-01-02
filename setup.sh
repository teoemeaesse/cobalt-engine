#!/bin/bash

cd lib/glew/auto && sudo make && cd .. && sudo make && sudo make install
cd ../glfw && cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -S . -B build && cd build && sudo make