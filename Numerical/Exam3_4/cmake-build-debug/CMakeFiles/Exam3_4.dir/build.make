# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_SOURCE_DIR = /Users/Steven/CLionProjects/Exam3_4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Steven/CLionProjects/Exam3_4/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Exam3_4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Exam3_4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Exam3_4.dir/flags.make

CMakeFiles/Exam3_4.dir/main.cpp.o: CMakeFiles/Exam3_4.dir/flags.make
CMakeFiles/Exam3_4.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Steven/CLionProjects/Exam3_4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Exam3_4.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Exam3_4.dir/main.cpp.o -c /Users/Steven/CLionProjects/Exam3_4/main.cpp

CMakeFiles/Exam3_4.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Exam3_4.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Steven/CLionProjects/Exam3_4/main.cpp > CMakeFiles/Exam3_4.dir/main.cpp.i

CMakeFiles/Exam3_4.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Exam3_4.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Steven/CLionProjects/Exam3_4/main.cpp -o CMakeFiles/Exam3_4.dir/main.cpp.s

CMakeFiles/Exam3_4.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Exam3_4.dir/main.cpp.o.requires

CMakeFiles/Exam3_4.dir/main.cpp.o.provides: CMakeFiles/Exam3_4.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Exam3_4.dir/build.make CMakeFiles/Exam3_4.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Exam3_4.dir/main.cpp.o.provides

CMakeFiles/Exam3_4.dir/main.cpp.o.provides.build: CMakeFiles/Exam3_4.dir/main.cpp.o


# Object files for target Exam3_4
Exam3_4_OBJECTS = \
"CMakeFiles/Exam3_4.dir/main.cpp.o"

# External object files for target Exam3_4
Exam3_4_EXTERNAL_OBJECTS =

Exam3_4: CMakeFiles/Exam3_4.dir/main.cpp.o
Exam3_4: CMakeFiles/Exam3_4.dir/build.make
Exam3_4: CMakeFiles/Exam3_4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Steven/CLionProjects/Exam3_4/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Exam3_4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Exam3_4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Exam3_4.dir/build: Exam3_4

.PHONY : CMakeFiles/Exam3_4.dir/build

CMakeFiles/Exam3_4.dir/requires: CMakeFiles/Exam3_4.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Exam3_4.dir/requires

CMakeFiles/Exam3_4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Exam3_4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Exam3_4.dir/clean

CMakeFiles/Exam3_4.dir/depend:
	cd /Users/Steven/CLionProjects/Exam3_4/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Steven/CLionProjects/Exam3_4 /Users/Steven/CLionProjects/Exam3_4 /Users/Steven/CLionProjects/Exam3_4/cmake-build-debug /Users/Steven/CLionProjects/Exam3_4/cmake-build-debug /Users/Steven/CLionProjects/Exam3_4/cmake-build-debug/CMakeFiles/Exam3_4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Exam3_4.dir/depend

