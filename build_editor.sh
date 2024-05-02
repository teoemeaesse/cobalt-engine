#!/bin/bash

usage() {
    echo "Usage: $0 [options]"
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
            echo "Unknown option: $arg"
            usage
            exit 1
            ;;
    esac
done

mkdir -p build
cd build || exit 1

if [ "$RELEASE" -eq 1 ]; then
    cmake -DTEST_ENVIRONMENT=OFF -DCMAKE_BUILD_TYPE=Release ..
else
    cmake -DTEST_ENVIRONMENT=OFF ..
fi

cmake --build .

if [ "$RUN" -eq 1 ]; then
    cd .. && ./build/bin/cobalt
fi
