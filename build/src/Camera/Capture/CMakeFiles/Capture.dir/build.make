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
include src/Camera/Capture/CMakeFiles/Capture.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/Camera/Capture/CMakeFiles/Capture.dir/compiler_depend.make

# Include the progress variables for this target.
include src/Camera/Capture/CMakeFiles/Capture.dir/progress.make

# Include the compile flags for this target's objects.
include src/Camera/Capture/CMakeFiles/Capture.dir/flags.make

src/Camera/Capture/CMakeFiles/Capture.dir/VideoCapture.cpp.o: src/Camera/Capture/CMakeFiles/Capture.dir/flags.make
src/Camera/Capture/CMakeFiles/Capture.dir/VideoCapture.cpp.o: /home/arca/Documents/codebases/Prediction2425/src/Camera/Capture/VideoCapture.cpp
src/Camera/Capture/CMakeFiles/Capture.dir/VideoCapture.cpp.o: src/Camera/Capture/CMakeFiles/Capture.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/arca/Documents/codebases/Prediction2425/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Camera/Capture/CMakeFiles/Capture.dir/VideoCapture.cpp.o"
	cd /home/arca/Documents/codebases/Prediction2425/build/src/Camera/Capture && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Camera/Capture/CMakeFiles/Capture.dir/VideoCapture.cpp.o -MF CMakeFiles/Capture.dir/VideoCapture.cpp.o.d -o CMakeFiles/Capture.dir/VideoCapture.cpp.o -c /home/arca/Documents/codebases/Prediction2425/src/Camera/Capture/VideoCapture.cpp

src/Camera/Capture/CMakeFiles/Capture.dir/VideoCapture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Capture.dir/VideoCapture.cpp.i"
	cd /home/arca/Documents/codebases/Prediction2425/build/src/Camera/Capture && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arca/Documents/codebases/Prediction2425/src/Camera/Capture/VideoCapture.cpp > CMakeFiles/Capture.dir/VideoCapture.cpp.i

src/Camera/Capture/CMakeFiles/Capture.dir/VideoCapture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Capture.dir/VideoCapture.cpp.s"
	cd /home/arca/Documents/codebases/Prediction2425/build/src/Camera/Capture && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arca/Documents/codebases/Prediction2425/src/Camera/Capture/VideoCapture.cpp -o CMakeFiles/Capture.dir/VideoCapture.cpp.s

# Object files for target Capture
Capture_OBJECTS = \
"CMakeFiles/Capture.dir/VideoCapture.cpp.o"

# External object files for target Capture
Capture_EXTERNAL_OBJECTS =

src/Camera/Capture/libCapture.a: src/Camera/Capture/CMakeFiles/Capture.dir/VideoCapture.cpp.o
src/Camera/Capture/libCapture.a: src/Camera/Capture/CMakeFiles/Capture.dir/build.make
src/Camera/Capture/libCapture.a: src/Camera/Capture/CMakeFiles/Capture.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/arca/Documents/codebases/Prediction2425/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libCapture.a"
	cd /home/arca/Documents/codebases/Prediction2425/build/src/Camera/Capture && $(CMAKE_COMMAND) -P CMakeFiles/Capture.dir/cmake_clean_target.cmake
	cd /home/arca/Documents/codebases/Prediction2425/build/src/Camera/Capture && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Capture.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Camera/Capture/CMakeFiles/Capture.dir/build: src/Camera/Capture/libCapture.a
.PHONY : src/Camera/Capture/CMakeFiles/Capture.dir/build

src/Camera/Capture/CMakeFiles/Capture.dir/clean:
	cd /home/arca/Documents/codebases/Prediction2425/build/src/Camera/Capture && $(CMAKE_COMMAND) -P CMakeFiles/Capture.dir/cmake_clean.cmake
.PHONY : src/Camera/Capture/CMakeFiles/Capture.dir/clean

src/Camera/Capture/CMakeFiles/Capture.dir/depend:
	cd /home/arca/Documents/codebases/Prediction2425/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arca/Documents/codebases/Prediction2425 /home/arca/Documents/codebases/Prediction2425/src/Camera/Capture /home/arca/Documents/codebases/Prediction2425/build /home/arca/Documents/codebases/Prediction2425/build/src/Camera/Capture /home/arca/Documents/codebases/Prediction2425/build/src/Camera/Capture/CMakeFiles/Capture.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/Camera/Capture/CMakeFiles/Capture.dir/depend
