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
CMAKE_SOURCE_DIR = /Users/Steven/CLionProjects/HW5_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Steven/CLionProjects/HW5_2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HW5_2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HW5_2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HW5_2.dir/flags.make

CMakeFiles/HW5_2.dir/main.cpp.o: CMakeFiles/HW5_2.dir/flags.make
CMakeFiles/HW5_2.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Steven/CLionProjects/HW5_2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HW5_2.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HW5_2.dir/main.cpp.o -c /Users/Steven/CLionProjects/HW5_2/main.cpp

CMakeFiles/HW5_2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW5_2.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Steven/CLionProjects/HW5_2/main.cpp > CMakeFiles/HW5_2.dir/main.cpp.i

CMakeFiles/HW5_2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW5_2.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Steven/CLionProjects/HW5_2/main.cpp -o CMakeFiles/HW5_2.dir/main.cpp.s

CMakeFiles/HW5_2.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/HW5_2.dir/main.cpp.o.requires

CMakeFiles/HW5_2.dir/main.cpp.o.provides: CMakeFiles/HW5_2.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/HW5_2.dir/build.make CMakeFiles/HW5_2.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/HW5_2.dir/main.cpp.o.provides

CMakeFiles/HW5_2.dir/main.cpp.o.provides.build: CMakeFiles/HW5_2.dir/main.cpp.o


# Object files for target HW5_2
HW5_2_OBJECTS = \
"CMakeFiles/HW5_2.dir/main.cpp.o"

# External object files for target HW5_2
HW5_2_EXTERNAL_OBJECTS =

HW5_2: CMakeFiles/HW5_2.dir/main.cpp.o
HW5_2: CMakeFiles/HW5_2.dir/build.make
HW5_2: CMakeFiles/HW5_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Steven/CLionProjects/HW5_2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HW5_2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HW5_2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HW5_2.dir/build: HW5_2

.PHONY : CMakeFiles/HW5_2.dir/build

CMakeFiles/HW5_2.dir/requires: CMakeFiles/HW5_2.dir/main.cpp.o.requires

.PHONY : CMakeFiles/HW5_2.dir/requires

CMakeFiles/HW5_2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HW5_2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HW5_2.dir/clean

CMakeFiles/HW5_2.dir/depend:
	cd /Users/Steven/CLionProjects/HW5_2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Steven/CLionProjects/HW5_2 /Users/Steven/CLionProjects/HW5_2 /Users/Steven/CLionProjects/HW5_2/cmake-build-debug /Users/Steven/CLionProjects/HW5_2/cmake-build-debug /Users/Steven/CLionProjects/HW5_2/cmake-build-debug/CMakeFiles/HW5_2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HW5_2.dir/depend
