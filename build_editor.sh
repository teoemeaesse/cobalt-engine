#!/bin/bash

mkdir -p build && cd build

cmake -DTEST_ENVIRONMENT=ON ..

cmake --build .