#!/bin/bash

cd tests

mkdir -p build && cd build

cmake ..

cmake --build .

make test