# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ariell/Education/intro-to-c/snake/snippet-code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ariell/Education/intro-to-c/snake/snippet-code/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/snippet_code.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/snippet_code.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/snippet_code.dir/flags.make

CMakeFiles/snippet_code.dir/main.c.o: CMakeFiles/snippet_code.dir/flags.make
CMakeFiles/snippet_code.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ariell/Education/intro-to-c/snake/snippet-code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/snippet_code.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/snippet_code.dir/main.c.o   -c /Users/ariell/Education/intro-to-c/snake/snippet-code/main.c

CMakeFiles/snippet_code.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/snippet_code.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ariell/Education/intro-to-c/snake/snippet-code/main.c > CMakeFiles/snippet_code.dir/main.c.i

CMakeFiles/snippet_code.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/snippet_code.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ariell/Education/intro-to-c/snake/snippet-code/main.c -o CMakeFiles/snippet_code.dir/main.c.s

# Object files for target snippet_code
snippet_code_OBJECTS = \
"CMakeFiles/snippet_code.dir/main.c.o"

# External object files for target snippet_code
snippet_code_EXTERNAL_OBJECTS =

snippet_code: CMakeFiles/snippet_code.dir/main.c.o
snippet_code: CMakeFiles/snippet_code.dir/build.make
snippet_code: CMakeFiles/snippet_code.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ariell/Education/intro-to-c/snake/snippet-code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable snippet_code"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/snippet_code.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/snippet_code.dir/build: snippet_code

.PHONY : CMakeFiles/snippet_code.dir/build

CMakeFiles/snippet_code.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/snippet_code.dir/cmake_clean.cmake
.PHONY : CMakeFiles/snippet_code.dir/clean

CMakeFiles/snippet_code.dir/depend:
	cd /Users/ariell/Education/intro-to-c/snake/snippet-code/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ariell/Education/intro-to-c/snake/snippet-code /Users/ariell/Education/intro-to-c/snake/snippet-code /Users/ariell/Education/intro-to-c/snake/snippet-code/cmake-build-debug /Users/ariell/Education/intro-to-c/snake/snippet-code/cmake-build-debug /Users/ariell/Education/intro-to-c/snake/snippet-code/cmake-build-debug/CMakeFiles/snippet_code.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/snippet_code.dir/depend

