# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/97252/Documents/GitHub/ProcessSync

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/97252/Documents/GitHub/ProcessSync/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ProcessSync.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ProcessSync.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ProcessSync.dir/flags.make

CMakeFiles/ProcessSync.dir/server.c.o: CMakeFiles/ProcessSync.dir/flags.make
CMakeFiles/ProcessSync.dir/server.c.o: ../server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/97252/Documents/GitHub/ProcessSync/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ProcessSync.dir/server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ProcessSync.dir/server.c.o   -c /mnt/c/Users/97252/Documents/GitHub/ProcessSync/server.c

CMakeFiles/ProcessSync.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ProcessSync.dir/server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/97252/Documents/GitHub/ProcessSync/server.c > CMakeFiles/ProcessSync.dir/server.c.i

CMakeFiles/ProcessSync.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ProcessSync.dir/server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/97252/Documents/GitHub/ProcessSync/server.c -o CMakeFiles/ProcessSync.dir/server.c.s

CMakeFiles/ProcessSync.dir/Test.c.o: CMakeFiles/ProcessSync.dir/flags.make
CMakeFiles/ProcessSync.dir/Test.c.o: ../Test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/97252/Documents/GitHub/ProcessSync/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ProcessSync.dir/Test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ProcessSync.dir/Test.c.o   -c /mnt/c/Users/97252/Documents/GitHub/ProcessSync/Test.c

CMakeFiles/ProcessSync.dir/Test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ProcessSync.dir/Test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/97252/Documents/GitHub/ProcessSync/Test.c > CMakeFiles/ProcessSync.dir/Test.c.i

CMakeFiles/ProcessSync.dir/Test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ProcessSync.dir/Test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/97252/Documents/GitHub/ProcessSync/Test.c -o CMakeFiles/ProcessSync.dir/Test.c.s

# Object files for target ProcessSync
ProcessSync_OBJECTS = \
"CMakeFiles/ProcessSync.dir/server.c.o" \
"CMakeFiles/ProcessSync.dir/Test.c.o"

# External object files for target ProcessSync
ProcessSync_EXTERNAL_OBJECTS =

ProcessSync: CMakeFiles/ProcessSync.dir/server.c.o
ProcessSync: CMakeFiles/ProcessSync.dir/Test.c.o
ProcessSync: CMakeFiles/ProcessSync.dir/build.make
ProcessSync: CMakeFiles/ProcessSync.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/97252/Documents/GitHub/ProcessSync/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ProcessSync"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ProcessSync.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ProcessSync.dir/build: ProcessSync

.PHONY : CMakeFiles/ProcessSync.dir/build

CMakeFiles/ProcessSync.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ProcessSync.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ProcessSync.dir/clean

CMakeFiles/ProcessSync.dir/depend:
	cd /mnt/c/Users/97252/Documents/GitHub/ProcessSync/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/97252/Documents/GitHub/ProcessSync /mnt/c/Users/97252/Documents/GitHub/ProcessSync /mnt/c/Users/97252/Documents/GitHub/ProcessSync/cmake-build-debug /mnt/c/Users/97252/Documents/GitHub/ProcessSync/cmake-build-debug /mnt/c/Users/97252/Documents/GitHub/ProcessSync/cmake-build-debug/CMakeFiles/ProcessSync.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ProcessSync.dir/depend

