#!/bin/bash

cd lib

ln -s $(which python3) $(dirname $(which python3))/python
cd glew/auto && sudo make && cd .. && sudo make && sudo make install

cd ..

cd glfw && cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -S . -B build && cd build && sudo make