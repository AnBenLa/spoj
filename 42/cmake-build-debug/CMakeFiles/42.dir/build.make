# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /cygdrive/c/Users/Mortiferum/.CLion2019.2/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Mortiferum/.CLion2019.2/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/Mortiferum/CLionProjects/spoj/42

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/Mortiferum/CLionProjects/spoj/42/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/42.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/42.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/42.dir/flags.make

CMakeFiles/42.dir/main.cpp.o: CMakeFiles/42.dir/flags.make
CMakeFiles/42.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Mortiferum/CLionProjects/spoj/42/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/42.dir/main.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/42.dir/main.cpp.o -c /cygdrive/c/Users/Mortiferum/CLionProjects/spoj/42/main.cpp

CMakeFiles/42.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/42.dir/main.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/Mortiferum/CLionProjects/spoj/42/main.cpp > CMakeFiles/42.dir/main.cpp.i

CMakeFiles/42.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/42.dir/main.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/Mortiferum/CLionProjects/spoj/42/main.cpp -o CMakeFiles/42.dir/main.cpp.s

# Object files for target 42
42_OBJECTS = \
"CMakeFiles/42.dir/main.cpp.o"

# External object files for target 42
42_EXTERNAL_OBJECTS =

42.exe: CMakeFiles/42.dir/main.cpp.o
42.exe: CMakeFiles/42.dir/build.make
42.exe: CMakeFiles/42.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Mortiferum/CLionProjects/spoj/42/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 42.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/42.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/42.dir/build: 42.exe

.PHONY : CMakeFiles/42.dir/build

CMakeFiles/42.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/42.dir/cmake_clean.cmake
.PHONY : CMakeFiles/42.dir/clean

CMakeFiles/42.dir/depend:
	cd /cygdrive/c/Users/Mortiferum/CLionProjects/spoj/42/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Mortiferum/CLionProjects/spoj/42 /cygdrive/c/Users/Mortiferum/CLionProjects/spoj/42 /cygdrive/c/Users/Mortiferum/CLionProjects/spoj/42/cmake-build-debug /cygdrive/c/Users/Mortiferum/CLionProjects/spoj/42/cmake-build-debug /cygdrive/c/Users/Mortiferum/CLionProjects/spoj/42/cmake-build-debug/CMakeFiles/42.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/42.dir/depend

