# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/esdeath/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/173.4548.31/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/esdeath/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/173.4548.31/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/esdeath/CLionProjects/The Matrix"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/esdeath/CLionProjects/The Matrix/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/The_Matrix.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/The_Matrix.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/The_Matrix.dir/flags.make

CMakeFiles/The_Matrix.dir/main.cpp.o: CMakeFiles/The_Matrix.dir/flags.make
CMakeFiles/The_Matrix.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/esdeath/CLionProjects/The Matrix/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/The_Matrix.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/The_Matrix.dir/main.cpp.o -c "/home/esdeath/CLionProjects/The Matrix/main.cpp"

CMakeFiles/The_Matrix.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/The_Matrix.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/esdeath/CLionProjects/The Matrix/main.cpp" > CMakeFiles/The_Matrix.dir/main.cpp.i

CMakeFiles/The_Matrix.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/The_Matrix.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/esdeath/CLionProjects/The Matrix/main.cpp" -o CMakeFiles/The_Matrix.dir/main.cpp.s

CMakeFiles/The_Matrix.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/The_Matrix.dir/main.cpp.o.requires

CMakeFiles/The_Matrix.dir/main.cpp.o.provides: CMakeFiles/The_Matrix.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/The_Matrix.dir/build.make CMakeFiles/The_Matrix.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/The_Matrix.dir/main.cpp.o.provides

CMakeFiles/The_Matrix.dir/main.cpp.o.provides.build: CMakeFiles/The_Matrix.dir/main.cpp.o


CMakeFiles/The_Matrix.dir/matrix.cpp.o: CMakeFiles/The_Matrix.dir/flags.make
CMakeFiles/The_Matrix.dir/matrix.cpp.o: ../matrix.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/esdeath/CLionProjects/The Matrix/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/The_Matrix.dir/matrix.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/The_Matrix.dir/matrix.cpp.o -c "/home/esdeath/CLionProjects/The Matrix/matrix.cpp"

CMakeFiles/The_Matrix.dir/matrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/The_Matrix.dir/matrix.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/esdeath/CLionProjects/The Matrix/matrix.cpp" > CMakeFiles/The_Matrix.dir/matrix.cpp.i

CMakeFiles/The_Matrix.dir/matrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/The_Matrix.dir/matrix.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/esdeath/CLionProjects/The Matrix/matrix.cpp" -o CMakeFiles/The_Matrix.dir/matrix.cpp.s

CMakeFiles/The_Matrix.dir/matrix.cpp.o.requires:

.PHONY : CMakeFiles/The_Matrix.dir/matrix.cpp.o.requires

CMakeFiles/The_Matrix.dir/matrix.cpp.o.provides: CMakeFiles/The_Matrix.dir/matrix.cpp.o.requires
	$(MAKE) -f CMakeFiles/The_Matrix.dir/build.make CMakeFiles/The_Matrix.dir/matrix.cpp.o.provides.build
.PHONY : CMakeFiles/The_Matrix.dir/matrix.cpp.o.provides

CMakeFiles/The_Matrix.dir/matrix.cpp.o.provides.build: CMakeFiles/The_Matrix.dir/matrix.cpp.o


# Object files for target The_Matrix
The_Matrix_OBJECTS = \
"CMakeFiles/The_Matrix.dir/main.cpp.o" \
"CMakeFiles/The_Matrix.dir/matrix.cpp.o"

# External object files for target The_Matrix
The_Matrix_EXTERNAL_OBJECTS =

The_Matrix: CMakeFiles/The_Matrix.dir/main.cpp.o
The_Matrix: CMakeFiles/The_Matrix.dir/matrix.cpp.o
The_Matrix: CMakeFiles/The_Matrix.dir/build.make
The_Matrix: CMakeFiles/The_Matrix.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/esdeath/CLionProjects/The Matrix/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable The_Matrix"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/The_Matrix.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/The_Matrix.dir/build: The_Matrix

.PHONY : CMakeFiles/The_Matrix.dir/build

CMakeFiles/The_Matrix.dir/requires: CMakeFiles/The_Matrix.dir/main.cpp.o.requires
CMakeFiles/The_Matrix.dir/requires: CMakeFiles/The_Matrix.dir/matrix.cpp.o.requires

.PHONY : CMakeFiles/The_Matrix.dir/requires

CMakeFiles/The_Matrix.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/The_Matrix.dir/cmake_clean.cmake
.PHONY : CMakeFiles/The_Matrix.dir/clean

CMakeFiles/The_Matrix.dir/depend:
	cd "/home/esdeath/CLionProjects/The Matrix/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/esdeath/CLionProjects/The Matrix" "/home/esdeath/CLionProjects/The Matrix" "/home/esdeath/CLionProjects/The Matrix/cmake-build-debug" "/home/esdeath/CLionProjects/The Matrix/cmake-build-debug" "/home/esdeath/CLionProjects/The Matrix/cmake-build-debug/CMakeFiles/The_Matrix.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/The_Matrix.dir/depend

