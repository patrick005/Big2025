# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/aa/Big2025

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aa/Big2025

# Include any dependencies generated for this target.
include c_example/part2/CMakeFiles/passFail.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include c_example/part2/CMakeFiles/passFail.dir/compiler_depend.make

# Include the progress variables for this target.
include c_example/part2/CMakeFiles/passFail.dir/progress.make

# Include the compile flags for this target's objects.
include c_example/part2/CMakeFiles/passFail.dir/flags.make

c_example/part2/CMakeFiles/passFail.dir/passFail.c.o: c_example/part2/CMakeFiles/passFail.dir/flags.make
c_example/part2/CMakeFiles/passFail.dir/passFail.c.o: c_example/part2/passFail.c
c_example/part2/CMakeFiles/passFail.dir/passFail.c.o: c_example/part2/CMakeFiles/passFail.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aa/Big2025/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object c_example/part2/CMakeFiles/passFail.dir/passFail.c.o"
	cd /home/aa/Big2025/c_example/part2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT c_example/part2/CMakeFiles/passFail.dir/passFail.c.o -MF CMakeFiles/passFail.dir/passFail.c.o.d -o CMakeFiles/passFail.dir/passFail.c.o -c /home/aa/Big2025/c_example/part2/passFail.c

c_example/part2/CMakeFiles/passFail.dir/passFail.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/passFail.dir/passFail.c.i"
	cd /home/aa/Big2025/c_example/part2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aa/Big2025/c_example/part2/passFail.c > CMakeFiles/passFail.dir/passFail.c.i

c_example/part2/CMakeFiles/passFail.dir/passFail.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/passFail.dir/passFail.c.s"
	cd /home/aa/Big2025/c_example/part2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aa/Big2025/c_example/part2/passFail.c -o CMakeFiles/passFail.dir/passFail.c.s

# Object files for target passFail
passFail_OBJECTS = \
"CMakeFiles/passFail.dir/passFail.c.o"

# External object files for target passFail
passFail_EXTERNAL_OBJECTS =

c_example/part2/passFail: c_example/part2/CMakeFiles/passFail.dir/passFail.c.o
c_example/part2/passFail: c_example/part2/CMakeFiles/passFail.dir/build.make
c_example/part2/passFail: c_example/part2/CMakeFiles/passFail.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aa/Big2025/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable passFail"
	cd /home/aa/Big2025/c_example/part2 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/passFail.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
c_example/part2/CMakeFiles/passFail.dir/build: c_example/part2/passFail
.PHONY : c_example/part2/CMakeFiles/passFail.dir/build

c_example/part2/CMakeFiles/passFail.dir/clean:
	cd /home/aa/Big2025/c_example/part2 && $(CMAKE_COMMAND) -P CMakeFiles/passFail.dir/cmake_clean.cmake
.PHONY : c_example/part2/CMakeFiles/passFail.dir/clean

c_example/part2/CMakeFiles/passFail.dir/depend:
	cd /home/aa/Big2025 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aa/Big2025 /home/aa/Big2025/c_example/part2 /home/aa/Big2025 /home/aa/Big2025/c_example/part2 /home/aa/Big2025/c_example/part2/CMakeFiles/passFail.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : c_example/part2/CMakeFiles/passFail.dir/depend

