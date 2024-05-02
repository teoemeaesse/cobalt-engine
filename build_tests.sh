#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${GREEN}Navigating to tests directory...${NC}"
cd tests

echo -e "${GREEN}Creating and entering build directory...${NC}"
mkdir -p build && cd build

echo -e "${GREEN}Configuring tests with CMake...${NC}"
cmake -DTEST_ENVIRONMENT=ON ..

echo -e "${GREEN}Building tests...${NC}"
cmake --build .

make test

if [ $? -eq 0 ]; then
    echo -e "${GREEN}Tests executed successfully.${NC}"
else
    echo -e "${RED}Tests failed. Check the output above for details.${NC}"
    exit 1
fi
