# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.1

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
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/d/OperatingSystems/Homework/PageSwapAlgorithms

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/d/OperatingSystems/Homework/PageSwapAlgorithms/build

# Include any dependencies generated for this target.
include CMakeFiles/SoneFivePaging.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SoneFivePaging.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SoneFivePaging.dir/flags.make

CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.o: CMakeFiles/SoneFivePaging.dir/flags.make
CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.o: ../src/S15Paging.c
	$(CMAKE_COMMAND) -E cmake_progress_report /cygdrive/d/OperatingSystems/Homework/PageSwapAlgorithms/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.o   -c /cygdrive/d/OperatingSystems/Homework/PageSwapAlgorithms/src/S15Paging.c

CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /cygdrive/d/OperatingSystems/Homework/PageSwapAlgorithms/src/S15Paging.c > CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.i

CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /cygdrive/d/OperatingSystems/Homework/PageSwapAlgorithms/src/S15Paging.c -o CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.s

CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.o.requires:
.PHONY : CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.o.requires

CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.o.provides: CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.o.requires
	$(MAKE) -f CMakeFiles/SoneFivePaging.dir/build.make CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.o.provides.build
.PHONY : CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.o.provides

CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.o.provides.build: CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.o

CMakeFiles/SoneFivePaging.dir/src/dll.c.o: CMakeFiles/SoneFivePaging.dir/flags.make
CMakeFiles/SoneFivePaging.dir/src/dll.c.o: ../src/dll.c
	$(CMAKE_COMMAND) -E cmake_progress_report /cygdrive/d/OperatingSystems/Homework/PageSwapAlgorithms/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/SoneFivePaging.dir/src/dll.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/SoneFivePaging.dir/src/dll.c.o   -c /cygdrive/d/OperatingSystems/Homework/PageSwapAlgorithms/src/dll.c

CMakeFiles/SoneFivePaging.dir/src/dll.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SoneFivePaging.dir/src/dll.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /cygdrive/d/OperatingSystems/Homework/PageSwapAlgorithms/src/dll.c > CMakeFiles/SoneFivePaging.dir/src/dll.c.i

CMakeFiles/SoneFivePaging.dir/src/dll.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SoneFivePaging.dir/src/dll.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /cygdrive/d/OperatingSystems/Homework/PageSwapAlgorithms/src/dll.c -o CMakeFiles/SoneFivePaging.dir/src/dll.c.s

CMakeFiles/SoneFivePaging.dir/src/dll.c.o.requires:
.PHONY : CMakeFiles/SoneFivePaging.dir/src/dll.c.o.requires

CMakeFiles/SoneFivePaging.dir/src/dll.c.o.provides: CMakeFiles/SoneFivePaging.dir/src/dll.c.o.requires
	$(MAKE) -f CMakeFiles/SoneFivePaging.dir/build.make CMakeFiles/SoneFivePaging.dir/src/dll.c.o.provides.build
.PHONY : CMakeFiles/SoneFivePaging.dir/src/dll.c.o.provides

CMakeFiles/SoneFivePaging.dir/src/dll.c.o.provides.build: CMakeFiles/SoneFivePaging.dir/src/dll.c.o

# Object files for target SoneFivePaging
SoneFivePaging_OBJECTS = \
"CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.o" \
"CMakeFiles/SoneFivePaging.dir/src/dll.c.o"

# External object files for target SoneFivePaging
SoneFivePaging_EXTERNAL_OBJECTS =

cygSoneFivePaging.dll: CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.o
cygSoneFivePaging.dll: CMakeFiles/SoneFivePaging.dir/src/dll.c.o
cygSoneFivePaging.dll: CMakeFiles/SoneFivePaging.dir/build.make
cygSoneFivePaging.dll: CMakeFiles/SoneFivePaging.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library cygSoneFivePaging.dll"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SoneFivePaging.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SoneFivePaging.dir/build: cygSoneFivePaging.dll
.PHONY : CMakeFiles/SoneFivePaging.dir/build

CMakeFiles/SoneFivePaging.dir/requires: CMakeFiles/SoneFivePaging.dir/src/S15Paging.c.o.requires
CMakeFiles/SoneFivePaging.dir/requires: CMakeFiles/SoneFivePaging.dir/src/dll.c.o.requires
.PHONY : CMakeFiles/SoneFivePaging.dir/requires

CMakeFiles/SoneFivePaging.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SoneFivePaging.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SoneFivePaging.dir/clean

CMakeFiles/SoneFivePaging.dir/depend:
	cd /cygdrive/d/OperatingSystems/Homework/PageSwapAlgorithms/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/d/OperatingSystems/Homework/PageSwapAlgorithms /cygdrive/d/OperatingSystems/Homework/PageSwapAlgorithms /cygdrive/d/OperatingSystems/Homework/PageSwapAlgorithms/build /cygdrive/d/OperatingSystems/Homework/PageSwapAlgorithms/build /cygdrive/d/OperatingSystems/Homework/PageSwapAlgorithms/build/CMakeFiles/SoneFivePaging.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SoneFivePaging.dir/depend

