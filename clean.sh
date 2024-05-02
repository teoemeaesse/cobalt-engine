#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

remove_dir() {
    local dir=$1
    if [ -d "$dir" ]; then
        echo -e "${GREEN}Removing $dir directory...${NC}"
        rm -rf "$dir"
        echo -e "${GREEN}$dir directory removed successfully.${NC}"
    else
        echo -e "${RED}$dir directory does not exist. No action taken.${NC}"
    fi
}

echo -e "${GREEN}Starting cleanup of build directories...${NC}"

remove_dir build

remove_dir tests/build

echo -e "${GREEN}Cleanup completed.${NC}"
