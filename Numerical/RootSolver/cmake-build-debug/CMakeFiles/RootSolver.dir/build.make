# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Steven/CLionProjects/RootSolver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Steven/CLionProjects/RootSolver/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/RootSolver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RootSolver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RootSolver.dir/flags.make

CMakeFiles/RootSolver.dir/main.cpp.o: CMakeFiles/RootSolver.dir/flags.make
CMakeFiles/RootSolver.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Steven/CLionProjects/RootSolver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RootSolver.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RootSolver.dir/main.cpp.o -c /Users/Steven/CLionProjects/RootSolver/main.cpp

CMakeFiles/RootSolver.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RootSolver.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Steven/CLionProjects/RootSolver/main.cpp > CMakeFiles/RootSolver.dir/main.cpp.i

CMakeFiles/RootSolver.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RootSolver.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Steven/CLionProjects/RootSolver/main.cpp -o CMakeFiles/RootSolver.dir/main.cpp.s

CMakeFiles/RootSolver.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/RootSolver.dir/main.cpp.o.requires

CMakeFiles/RootSolver.dir/main.cpp.o.provides: CMakeFiles/RootSolver.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/RootSolver.dir/build.make CMakeFiles/RootSolver.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/RootSolver.dir/main.cpp.o.provides

CMakeFiles/RootSolver.dir/main.cpp.o.provides.build: CMakeFiles/RootSolver.dir/main.cpp.o


# Object files for target RootSolver
RootSolver_OBJECTS = \
"CMakeFiles/RootSolver.dir/main.cpp.o"

# External object files for target RootSolver
RootSolver_EXTERNAL_OBJECTS =

RootSolver: CMakeFiles/RootSolver.dir/main.cpp.o
RootSolver: CMakeFiles/RootSolver.dir/build.make
RootSolver: CMakeFiles/RootSolver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Steven/CLionProjects/RootSolver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RootSolver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RootSolver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RootSolver.dir/build: RootSolver

.PHONY : CMakeFiles/RootSolver.dir/build

CMakeFiles/RootSolver.dir/requires: CMakeFiles/RootSolver.dir/main.cpp.o.requires

.PHONY : CMakeFiles/RootSolver.dir/requires

CMakeFiles/RootSolver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RootSolver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RootSolver.dir/clean

CMakeFiles/RootSolver.dir/depend:
	cd /Users/Steven/CLionProjects/RootSolver/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Steven/CLionProjects/RootSolver /Users/Steven/CLionProjects/RootSolver /Users/Steven/CLionProjects/RootSolver/cmake-build-debug /Users/Steven/CLionProjects/RootSolver/cmake-build-debug /Users/Steven/CLionProjects/RootSolver/cmake-build-debug/CMakeFiles/RootSolver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RootSolver.dir/depend

