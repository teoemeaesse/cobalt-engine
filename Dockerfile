FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y gcc g++ cmake \
        xorg-dev \
        libgl1-mesa-dev \
        libglu1-mesa-dev \
        libxrandr-dev \
        libxinerama-dev \
        libxcursor-dev \
        libxi-dev \
        libxxf86vm-dev

# Set working directory
WORKDIR /app

# Copy your source code to the container
COPY . /app

# Clean up
RUN ./clean.sh

# Build GLEW && GLFW
RUN cd /app/tests/lib/glew && make && make install && make clean
RUN cd /app/tests/lib/glfw && cmake . && make

# Default command to run when starting the container
CMD ["./build_tests.sh"]