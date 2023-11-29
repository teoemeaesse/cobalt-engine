#!/bin/bash

cd example

mkdir -p build && cd build

cmake ..

cmake --build .