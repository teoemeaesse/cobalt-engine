# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/tomasmarques/cobalt-engine/include/glfw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/tomasmarques/cobalt-engine/include/glfw

# Include any dependencies generated for this target.
include examples/CMakeFiles/simple.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/CMakeFiles/simple.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/simple.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/simple.dir/flags.make

examples/simple.app/Contents/Resources/glfw.icns: examples/glfw.icns
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Copying OS X content examples/simple.app/Contents/Resources/glfw.icns"
	$(CMAKE_COMMAND) -E copy /Users/tomasmarques/cobalt-engine/include/glfw/examples/glfw.icns examples/simple.app/Contents/Resources/glfw.icns

examples/CMakeFiles/simple.dir/simple.c.o: examples/CMakeFiles/simple.dir/flags.make
examples/CMakeFiles/simple.dir/simple.c.o: examples/simple.c
examples/CMakeFiles/simple.dir/simple.c.o: examples/CMakeFiles/simple.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/tomasmarques/cobalt-engine/include/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object examples/CMakeFiles/simple.dir/simple.c.o"
	cd /Users/tomasmarques/cobalt-engine/include/glfw/examples && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT examples/CMakeFiles/simple.dir/simple.c.o -MF CMakeFiles/simple.dir/simple.c.o.d -o CMakeFiles/simple.dir/simple.c.o -c /Users/tomasmarques/cobalt-engine/include/glfw/examples/simple.c

examples/CMakeFiles/simple.dir/simple.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/simple.dir/simple.c.i"
	cd /Users/tomasmarques/cobalt-engine/include/glfw/examples && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/tomasmarques/cobalt-engine/include/glfw/examples/simple.c > CMakeFiles/simple.dir/simple.c.i

examples/CMakeFiles/simple.dir/simple.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/simple.dir/simple.c.s"
	cd /Users/tomasmarques/cobalt-engine/include/glfw/examples && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/tomasmarques/cobalt-engine/include/glfw/examples/simple.c -o CMakeFiles/simple.dir/simple.c.s

examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.o: examples/CMakeFiles/simple.dir/flags.make
examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.o: deps/glad_gl.c
examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.o: examples/CMakeFiles/simple.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/tomasmarques/cobalt-engine/include/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.o"
	cd /Users/tomasmarques/cobalt-engine/include/glfw/examples && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.o -MF CMakeFiles/simple.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/simple.dir/__/deps/glad_gl.c.o -c /Users/tomasmarques/cobalt-engine/include/glfw/deps/glad_gl.c

examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/simple.dir/__/deps/glad_gl.c.i"
	cd /Users/tomasmarques/cobalt-engine/include/glfw/examples && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/tomasmarques/cobalt-engine/include/glfw/deps/glad_gl.c > CMakeFiles/simple.dir/__/deps/glad_gl.c.i

examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/simple.dir/__/deps/glad_gl.c.s"
	cd /Users/tomasmarques/cobalt-engine/include/glfw/examples && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/tomasmarques/cobalt-engine/include/glfw/deps/glad_gl.c -o CMakeFiles/simple.dir/__/deps/glad_gl.c.s

# Object files for target simple
simple_OBJECTS = \
"CMakeFiles/simple.dir/simple.c.o" \
"CMakeFiles/simple.dir/__/deps/glad_gl.c.o"

# External object files for target simple
simple_EXTERNAL_OBJECTS =

examples/simple.app/Contents/MacOS/simple: examples/CMakeFiles/simple.dir/simple.c.o
examples/simple.app/Contents/MacOS/simple: examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.o
examples/simple.app/Contents/MacOS/simple: examples/CMakeFiles/simple.dir/build.make
examples/simple.app/Contents/MacOS/simple: src/libglfw3.a
examples/simple.app/Contents/MacOS/simple: examples/CMakeFiles/simple.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/tomasmarques/cobalt-engine/include/glfw/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable simple.app/Contents/MacOS/simple"
	cd /Users/tomasmarques/cobalt-engine/include/glfw/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simple.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/simple.dir/build: examples/simple.app/Contents/MacOS/simple
examples/CMakeFiles/simple.dir/build: examples/simple.app/Contents/Resources/glfw.icns
.PHONY : examples/CMakeFiles/simple.dir/build

examples/CMakeFiles/simple.dir/clean:
	cd /Users/tomasmarques/cobalt-engine/include/glfw/examples && $(CMAKE_COMMAND) -P CMakeFiles/simple.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/simple.dir/clean

examples/CMakeFiles/simple.dir/depend:
	cd /Users/tomasmarques/cobalt-engine/include/glfw && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/tomasmarques/cobalt-engine/include/glfw /Users/tomasmarques/cobalt-engine/include/glfw/examples /Users/tomasmarques/cobalt-engine/include/glfw /Users/tomasmarques/cobalt-engine/include/glfw/examples /Users/tomasmarques/cobalt-engine/include/glfw/examples/CMakeFiles/simple.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : examples/CMakeFiles/simple.dir/depend

