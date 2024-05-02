#!/bin/bash

usage() {
    echo "Usage: $0 [options]"
    echo "Options:"
    echo "  --open, -o       Open the generated documentation in the default browser."
    echo "  --help, -h       Display this help message."
}

OPEN=0
for arg in "$@"; do
    case $arg in
        --open|-o)
            OPEN=1
            shift # Remove --open or -o from processing
            ;;
        --help|-h)
            usage
            exit 0
            ;;
        *)
            # Unknown option
            echo "Unknown option: $arg"
            usage
            exit 1
            ;;
    esac
done

mkdir -p docs
mkdir -p build
cd build || exit 1

cmake --build . --target doc_doxygen

cd ..

if [ "$OPEN" -eq 1 ]; then
    open docs/html/index.html
fi
