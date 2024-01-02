#!/bin/bash

cd tests

mkdir -p build && cd build

cmake -DTEST_ENVIRONMENT=ON ..

cmake --build .

make test