#!/bin/bash

cd lib/glew/auto && sudo make && cd .. && sudo make && sudo make install
cd ../../glfw && cmake -S . -B build && cd build && sudo make