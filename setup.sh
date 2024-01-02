#!/bin/bash

cd lib/glew/auto && sudo make && cd .. && sudo make && sudo make install && sudo make clean
cd ../../glfw && cmake -S . -B build && cd build && sudo make