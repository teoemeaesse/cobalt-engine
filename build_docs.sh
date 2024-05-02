#!/bin/bash

mkdir -p docs
mkdir -p build && cd build

cmake --build . --target doc_doxygen

cd .. && open docs/html/index.html