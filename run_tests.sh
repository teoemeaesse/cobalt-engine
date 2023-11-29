#!/bin/bash

cd build

# Run the cmake command
cmake ..

# Run the cmake --build command
cmake --build .

# Run the make test command
make test