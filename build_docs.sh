#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

usage() {
    echo -e "Usage: $0 [options]"
    echo "Options:"
    echo "  --open, -o       Open the generated documentation in the default browser."
    echo "  --help, -h       Display this help message."
}

OPEN=0
for arg in "$@"; do
    case $arg in
        --open|-o)
            OPEN=1
            shift
            ;;
        --help|-h)
            usage
            exit 0
            ;;
        *)
            echo -e "${RED}Unknown option: $arg${NC}"
            usage
            exit 1
            ;;
    esac
done

echo -e "${GREEN}Creating build directory...${NC}"
mkdir -p build
cd build || (echo -e "${RED}Failed to enter build directory. Exiting...${NC}" && exit 1)

echo -e "${GREEN}Configuring CMake...${NC}"
cmake .. -DDOXYGEN_CONFIG_FILE=../doxygen/Doxyfile || (echo -e "${RED}CMake configuration failed. Exiting...${NC}" && exit 1)

echo -e "${GREEN}Building documentation with Doxygen...${NC}"
cmake --build . --target doc_doxygen

cd ..

if [ "$OPEN" -eq 1 ]; then
    echo -e "${GREEN}Opening the generated documentation in the default browser...${NC}"
    open docs/html/index.html
fi

echo -e "${GREEN}Documentation build script completed.${NC}"´