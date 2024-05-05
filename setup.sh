#!/bin/bash


GREEN='\033[0;32m'
NC='\033[0m'


echo -e "${GREEN}Navigating to the lib directory...${NC}"
cd lib


echo -e "${GREEN}Creating a symlink for python3 executable as 'python'...${NC}"
sudo ln -s $(which python3) $(dirname $(which python3))/python

echo -e "${GREEN}Building GLEW from the submodule...${NC}"
cd glew/auto && sudo make
echo -e "${GREEN}Auto-generated GLEW Makefiles.${NC}"
cd ..
sudo make
echo -e "${GREEN}Compiled GLEW library.${NC}"
sudo make install
echo -e "${GREEN}GLEW library installed system-wide.${NC}"


echo -e "${GREEN}Returning to lib directory...${NC}"
cd ..


echo -e "${GREEN}Configuring and building GLFW from the submodule...${NC}"
cd glfw 
echo -e "${GREEN}Configuring GLFW build settings...${NC}"
cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -S . -B build
echo -e "${GREEN}Building GLFW...${NC}"
cd build && sudo make
echo -e "${GREEN}GLFW built successfully.${NC}"
