# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /Applications/Qt/Tools/CMake/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/Qt/Tools/CMake/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Shared/data/_miao_up/3rd_libs/assimp_4.0.1_build

# Utility rule file for ContinuousUpdate.

# Include the progress variables for this target.
include test/CMakeFiles/ContinuousUpdate.dir/progress.make

test/CMakeFiles/ContinuousUpdate:
	cd /Users/Shared/data/_miao_up/3rd_libs/assimp_4.0.1_build/test && /Applications/Qt/Tools/CMake/CMake.app/Contents/bin/ctest -D ContinuousUpdate

ContinuousUpdate: test/CMakeFiles/ContinuousUpdate
ContinuousUpdate: test/CMakeFiles/ContinuousUpdate.dir/build.make

.PHONY : ContinuousUpdate

# Rule to build all files generated by this target.
test/CMakeFiles/ContinuousUpdate.dir/build: ContinuousUpdate

.PHONY : test/CMakeFiles/ContinuousUpdate.dir/build

test/CMakeFiles/ContinuousUpdate.dir/clean:
	cd /Users/Shared/data/_miao_up/3rd_libs/assimp_4.0.1_build/test && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousUpdate.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/ContinuousUpdate.dir/clean

test/CMakeFiles/ContinuousUpdate.dir/depend:
	cd /Users/Shared/data/_miao_up/3rd_libs/assimp_4.0.1_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1 /Users/Shared/data/_miao_up/3rd_libs/assimp-4.0.1/test /Users/Shared/data/_miao_up/3rd_libs/assimp_4.0.1_build /Users/Shared/data/_miao_up/3rd_libs/assimp_4.0.1_build/test /Users/Shared/data/_miao_up/3rd_libs/assimp_4.0.1_build/test/CMakeFiles/ContinuousUpdate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/ContinuousUpdate.dir/depend

