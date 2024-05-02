#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

usage() {
    echo -e "Usage: $0 [options]"
    echo "Options:"
    echo "  --run, -r        Run the executable after building."
    echo "  --release, -f    Build in release mode with optimizations."
    echo "  --help, -h       Display this help message."
}

RUN=0
RELEASE=0
for arg in "$@"; do
    case $arg in
        --run|-r)
            RUN=1
            ;;
        --release|-f)
            RELEASE=1
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

echo -e "${GREEN}Creating build directory and entering it...${NC}"
mkdir -p build
cd build || (echo -e "${RED}Failed to enter build directory. Exiting...${NC}" && exit 1)

if [ "$RELEASE" -eq 1 ]; then
    echo -e "${GREEN}Configuring for release build...${NC}"
    cmake -DTEST_ENVIRONMENT=OFF -DCMAKE_BUILD_TYPE=Release ..
else
    echo -e "${GREEN}Configuring for debug build...${NC}"
    cmake -DTEST_ENVIRONMENT=OFF ..
fi

echo -e "${GREEN}Building the project...${NC}"
cmake --build .

if [ "$RUN" -eq 1 ]; then
    echo -e "${GREEN}Running the executable...${NC}"
    cd .. && ./build/bin/cobalt
fi

echo -e "${GREEN}Build script completed.${NC}"
