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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/arca/Documents/codebases/Prediction2425

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arca/Documents/codebases/Prediction2425/build

# Include any dependencies generated for this target.
include src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/compiler_depend.make

# Include the progress variables for this target.
include src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/progress.make

# Include the compile flags for this target's objects.
include src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/flags.make

src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/AbstractFilter.cpp.o: src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/flags.make
src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/AbstractFilter.cpp.o: /home/arca/Documents/codebases/Prediction2425/src/Filter/AbstractFilter/AbstractFilter.cpp
src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/AbstractFilter.cpp.o: src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/arca/Documents/codebases/Prediction2425/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/AbstractFilter.cpp.o"
	cd /home/arca/Documents/codebases/Prediction2425/build/src/Filter/AbstractFilter && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/AbstractFilter.cpp.o -MF CMakeFiles/AbstractFilter.dir/AbstractFilter.cpp.o.d -o CMakeFiles/AbstractFilter.dir/AbstractFilter.cpp.o -c /home/arca/Documents/codebases/Prediction2425/src/Filter/AbstractFilter/AbstractFilter.cpp

src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/AbstractFilter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/AbstractFilter.dir/AbstractFilter.cpp.i"
	cd /home/arca/Documents/codebases/Prediction2425/build/src/Filter/AbstractFilter && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arca/Documents/codebases/Prediction2425/src/Filter/AbstractFilter/AbstractFilter.cpp > CMakeFiles/AbstractFilter.dir/AbstractFilter.cpp.i

src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/AbstractFilter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/AbstractFilter.dir/AbstractFilter.cpp.s"
	cd /home/arca/Documents/codebases/Prediction2425/build/src/Filter/AbstractFilter && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arca/Documents/codebases/Prediction2425/src/Filter/AbstractFilter/AbstractFilter.cpp -o CMakeFiles/AbstractFilter.dir/AbstractFilter.cpp.s

# Object files for target AbstractFilter
AbstractFilter_OBJECTS = \
"CMakeFiles/AbstractFilter.dir/AbstractFilter.cpp.o"

# External object files for target AbstractFilter
AbstractFilter_EXTERNAL_OBJECTS =

src/Filter/AbstractFilter/libAbstractFilter.a: src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/AbstractFilter.cpp.o
src/Filter/AbstractFilter/libAbstractFilter.a: src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/build.make
src/Filter/AbstractFilter/libAbstractFilter.a: src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/arca/Documents/codebases/Prediction2425/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libAbstractFilter.a"
	cd /home/arca/Documents/codebases/Prediction2425/build/src/Filter/AbstractFilter && $(CMAKE_COMMAND) -P CMakeFiles/AbstractFilter.dir/cmake_clean_target.cmake
	cd /home/arca/Documents/codebases/Prediction2425/build/src/Filter/AbstractFilter && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AbstractFilter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/build: src/Filter/AbstractFilter/libAbstractFilter.a
.PHONY : src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/build

src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/clean:
	cd /home/arca/Documents/codebases/Prediction2425/build/src/Filter/AbstractFilter && $(CMAKE_COMMAND) -P CMakeFiles/AbstractFilter.dir/cmake_clean.cmake
.PHONY : src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/clean

src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/depend:
	cd /home/arca/Documents/codebases/Prediction2425/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arca/Documents/codebases/Prediction2425 /home/arca/Documents/codebases/Prediction2425/src/Filter/AbstractFilter /home/arca/Documents/codebases/Prediction2425/build /home/arca/Documents/codebases/Prediction2425/build/src/Filter/AbstractFilter /home/arca/Documents/codebases/Prediction2425/build/src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/Filter/AbstractFilter/CMakeFiles/AbstractFilter.dir/depend
