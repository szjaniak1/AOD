# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_SOURCE_DIR = /home/szjaniak/Documents/Inf/semestr4/AOD/lista3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/szjaniak/Documents/Inf/semestr4/AOD/lista3/build

# Include any dependencies generated for this target.
include CMakeFiles/radixheap.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/radixheap.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/radixheap.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/radixheap.dir/flags.make

CMakeFiles/radixheap.dir/radixheap.cpp.o: CMakeFiles/radixheap.dir/flags.make
CMakeFiles/radixheap.dir/radixheap.cpp.o: /home/szjaniak/Documents/Inf/semestr4/AOD/lista3/radixheap.cpp
CMakeFiles/radixheap.dir/radixheap.cpp.o: CMakeFiles/radixheap.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/szjaniak/Documents/Inf/semestr4/AOD/lista3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/radixheap.dir/radixheap.cpp.o"
	/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/radixheap.dir/radixheap.cpp.o -MF CMakeFiles/radixheap.dir/radixheap.cpp.o.d -o CMakeFiles/radixheap.dir/radixheap.cpp.o -c /home/szjaniak/Documents/Inf/semestr4/AOD/lista3/radixheap.cpp

CMakeFiles/radixheap.dir/radixheap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/radixheap.dir/radixheap.cpp.i"
	/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/szjaniak/Documents/Inf/semestr4/AOD/lista3/radixheap.cpp > CMakeFiles/radixheap.dir/radixheap.cpp.i

CMakeFiles/radixheap.dir/radixheap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/radixheap.dir/radixheap.cpp.s"
	/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/szjaniak/Documents/Inf/semestr4/AOD/lista3/radixheap.cpp -o CMakeFiles/radixheap.dir/radixheap.cpp.s

# Object files for target radixheap
radixheap_OBJECTS = \
"CMakeFiles/radixheap.dir/radixheap.cpp.o"

# External object files for target radixheap
radixheap_EXTERNAL_OBJECTS =

libradixheap.a: CMakeFiles/radixheap.dir/radixheap.cpp.o
libradixheap.a: CMakeFiles/radixheap.dir/build.make
libradixheap.a: CMakeFiles/radixheap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/szjaniak/Documents/Inf/semestr4/AOD/lista3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libradixheap.a"
	$(CMAKE_COMMAND) -P CMakeFiles/radixheap.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/radixheap.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/radixheap.dir/build: libradixheap.a
.PHONY : CMakeFiles/radixheap.dir/build

CMakeFiles/radixheap.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/radixheap.dir/cmake_clean.cmake
.PHONY : CMakeFiles/radixheap.dir/clean

CMakeFiles/radixheap.dir/depend:
	cd /home/szjaniak/Documents/Inf/semestr4/AOD/lista3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/szjaniak/Documents/Inf/semestr4/AOD/lista3 /home/szjaniak/Documents/Inf/semestr4/AOD/lista3 /home/szjaniak/Documents/Inf/semestr4/AOD/lista3/build /home/szjaniak/Documents/Inf/semestr4/AOD/lista3/build /home/szjaniak/Documents/Inf/semestr4/AOD/lista3/build/CMakeFiles/radixheap.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/radixheap.dir/depend
