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
CMAKE_SOURCE_DIR = /media/sf_sharedf_VM/repobvn/cpp17/vs_cpp_ex

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/sf_sharedf_VM/repobvn/cpp17/vs_cpp_ex/build

# Include any dependencies generated for this target.
include CMakeFiles/shallowVsDeepCpy.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/shallowVsDeepCpy.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/shallowVsDeepCpy.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shallowVsDeepCpy.dir/flags.make

CMakeFiles/shallowVsDeepCpy.dir/shallowVsDeepCpy.cpp.o: CMakeFiles/shallowVsDeepCpy.dir/flags.make
CMakeFiles/shallowVsDeepCpy.dir/shallowVsDeepCpy.cpp.o: ../shallowVsDeepCpy.cpp
CMakeFiles/shallowVsDeepCpy.dir/shallowVsDeepCpy.cpp.o: CMakeFiles/shallowVsDeepCpy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/sf_sharedf_VM/repobvn/cpp17/vs_cpp_ex/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/shallowVsDeepCpy.dir/shallowVsDeepCpy.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/shallowVsDeepCpy.dir/shallowVsDeepCpy.cpp.o -MF CMakeFiles/shallowVsDeepCpy.dir/shallowVsDeepCpy.cpp.o.d -o CMakeFiles/shallowVsDeepCpy.dir/shallowVsDeepCpy.cpp.o -c /media/sf_sharedf_VM/repobvn/cpp17/vs_cpp_ex/shallowVsDeepCpy.cpp

CMakeFiles/shallowVsDeepCpy.dir/shallowVsDeepCpy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shallowVsDeepCpy.dir/shallowVsDeepCpy.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/sf_sharedf_VM/repobvn/cpp17/vs_cpp_ex/shallowVsDeepCpy.cpp > CMakeFiles/shallowVsDeepCpy.dir/shallowVsDeepCpy.cpp.i

CMakeFiles/shallowVsDeepCpy.dir/shallowVsDeepCpy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shallowVsDeepCpy.dir/shallowVsDeepCpy.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/sf_sharedf_VM/repobvn/cpp17/vs_cpp_ex/shallowVsDeepCpy.cpp -o CMakeFiles/shallowVsDeepCpy.dir/shallowVsDeepCpy.cpp.s

# Object files for target shallowVsDeepCpy
shallowVsDeepCpy_OBJECTS = \
"CMakeFiles/shallowVsDeepCpy.dir/shallowVsDeepCpy.cpp.o"

# External object files for target shallowVsDeepCpy
shallowVsDeepCpy_EXTERNAL_OBJECTS =

shallowVsDeepCpy: CMakeFiles/shallowVsDeepCpy.dir/shallowVsDeepCpy.cpp.o
shallowVsDeepCpy: CMakeFiles/shallowVsDeepCpy.dir/build.make
shallowVsDeepCpy: CMakeFiles/shallowVsDeepCpy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/sf_sharedf_VM/repobvn/cpp17/vs_cpp_ex/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable shallowVsDeepCpy"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shallowVsDeepCpy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shallowVsDeepCpy.dir/build: shallowVsDeepCpy
.PHONY : CMakeFiles/shallowVsDeepCpy.dir/build

CMakeFiles/shallowVsDeepCpy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/shallowVsDeepCpy.dir/cmake_clean.cmake
.PHONY : CMakeFiles/shallowVsDeepCpy.dir/clean

CMakeFiles/shallowVsDeepCpy.dir/depend:
	cd /media/sf_sharedf_VM/repobvn/cpp17/vs_cpp_ex/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/sf_sharedf_VM/repobvn/cpp17/vs_cpp_ex /media/sf_sharedf_VM/repobvn/cpp17/vs_cpp_ex /media/sf_sharedf_VM/repobvn/cpp17/vs_cpp_ex/build /media/sf_sharedf_VM/repobvn/cpp17/vs_cpp_ex/build /media/sf_sharedf_VM/repobvn/cpp17/vs_cpp_ex/build/CMakeFiles/shallowVsDeepCpy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/shallowVsDeepCpy.dir/depend
