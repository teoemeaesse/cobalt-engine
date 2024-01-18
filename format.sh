#!/bin/bash

find ./cobalt -iname "*.cpp" -o -iname "*.h" | xargs clang-format -i
find ./tests -iname "*.cpp" -o -iname "*.h" | xargs clang-format -i