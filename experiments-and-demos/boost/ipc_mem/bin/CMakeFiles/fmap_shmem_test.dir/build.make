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
CMAKE_SOURCE_DIR = /mnt/c/Users/Diana/Documents/OneDrive/OS/project/repo/experiments-and-demos/boost/ipc_mem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Diana/Documents/OneDrive/OS/project/repo/experiments-and-demos/boost/ipc_mem/bin

# Include any dependencies generated for this target.
include CMakeFiles/fmap_shmem_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fmap_shmem_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fmap_shmem_test.dir/flags.make

CMakeFiles/fmap_shmem_test.dir/src/fmap_shmem_test.cpp.o: CMakeFiles/fmap_shmem_test.dir/flags.make
CMakeFiles/fmap_shmem_test.dir/src/fmap_shmem_test.cpp.o: ../src/fmap_shmem_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Diana/Documents/OneDrive/OS/project/repo/experiments-and-demos/boost/ipc_mem/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fmap_shmem_test.dir/src/fmap_shmem_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fmap_shmem_test.dir/src/fmap_shmem_test.cpp.o -c /mnt/c/Users/Diana/Documents/OneDrive/OS/project/repo/experiments-and-demos/boost/ipc_mem/src/fmap_shmem_test.cpp

CMakeFiles/fmap_shmem_test.dir/src/fmap_shmem_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fmap_shmem_test.dir/src/fmap_shmem_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Diana/Documents/OneDrive/OS/project/repo/experiments-and-demos/boost/ipc_mem/src/fmap_shmem_test.cpp > CMakeFiles/fmap_shmem_test.dir/src/fmap_shmem_test.cpp.i

CMakeFiles/fmap_shmem_test.dir/src/fmap_shmem_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fmap_shmem_test.dir/src/fmap_shmem_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Diana/Documents/OneDrive/OS/project/repo/experiments-and-demos/boost/ipc_mem/src/fmap_shmem_test.cpp -o CMakeFiles/fmap_shmem_test.dir/src/fmap_shmem_test.cpp.s

# Object files for target fmap_shmem_test
fmap_shmem_test_OBJECTS = \
"CMakeFiles/fmap_shmem_test.dir/src/fmap_shmem_test.cpp.o"

# External object files for target fmap_shmem_test
fmap_shmem_test_EXTERNAL_OBJECTS =

../fmap_shmem_test: CMakeFiles/fmap_shmem_test.dir/src/fmap_shmem_test.cpp.o
../fmap_shmem_test: CMakeFiles/fmap_shmem_test.dir/build.make
../fmap_shmem_test: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
../fmap_shmem_test: /usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.71.0
../fmap_shmem_test: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
../fmap_shmem_test: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
../fmap_shmem_test: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.71.0
../fmap_shmem_test: CMakeFiles/fmap_shmem_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Diana/Documents/OneDrive/OS/project/repo/experiments-and-demos/boost/ipc_mem/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../fmap_shmem_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fmap_shmem_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fmap_shmem_test.dir/build: ../fmap_shmem_test

.PHONY : CMakeFiles/fmap_shmem_test.dir/build

CMakeFiles/fmap_shmem_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fmap_shmem_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fmap_shmem_test.dir/clean

CMakeFiles/fmap_shmem_test.dir/depend:
	cd /mnt/c/Users/Diana/Documents/OneDrive/OS/project/repo/experiments-and-demos/boost/ipc_mem/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Diana/Documents/OneDrive/OS/project/repo/experiments-and-demos/boost/ipc_mem /mnt/c/Users/Diana/Documents/OneDrive/OS/project/repo/experiments-and-demos/boost/ipc_mem /mnt/c/Users/Diana/Documents/OneDrive/OS/project/repo/experiments-and-demos/boost/ipc_mem/bin /mnt/c/Users/Diana/Documents/OneDrive/OS/project/repo/experiments-and-demos/boost/ipc_mem/bin /mnt/c/Users/Diana/Documents/OneDrive/OS/project/repo/experiments-and-demos/boost/ipc_mem/bin/CMakeFiles/fmap_shmem_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fmap_shmem_test.dir/depend

