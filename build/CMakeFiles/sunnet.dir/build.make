# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /root/cc_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/cc_project/build

# Include any dependencies generated for this target.
include CMakeFiles/sunnet.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sunnet.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sunnet.dir/flags.make

CMakeFiles/sunnet.dir/src/LuaAPI.cpp.o: CMakeFiles/sunnet.dir/flags.make
CMakeFiles/sunnet.dir/src/LuaAPI.cpp.o: ../src/LuaAPI.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/cc_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sunnet.dir/src/LuaAPI.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sunnet.dir/src/LuaAPI.cpp.o -c /root/cc_project/src/LuaAPI.cpp

CMakeFiles/sunnet.dir/src/LuaAPI.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sunnet.dir/src/LuaAPI.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/cc_project/src/LuaAPI.cpp > CMakeFiles/sunnet.dir/src/LuaAPI.cpp.i

CMakeFiles/sunnet.dir/src/LuaAPI.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sunnet.dir/src/LuaAPI.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/cc_project/src/LuaAPI.cpp -o CMakeFiles/sunnet.dir/src/LuaAPI.cpp.s

CMakeFiles/sunnet.dir/src/LuaAPI.cpp.o.requires:

.PHONY : CMakeFiles/sunnet.dir/src/LuaAPI.cpp.o.requires

CMakeFiles/sunnet.dir/src/LuaAPI.cpp.o.provides: CMakeFiles/sunnet.dir/src/LuaAPI.cpp.o.requires
	$(MAKE) -f CMakeFiles/sunnet.dir/build.make CMakeFiles/sunnet.dir/src/LuaAPI.cpp.o.provides.build
.PHONY : CMakeFiles/sunnet.dir/src/LuaAPI.cpp.o.provides

CMakeFiles/sunnet.dir/src/LuaAPI.cpp.o.provides.build: CMakeFiles/sunnet.dir/src/LuaAPI.cpp.o


CMakeFiles/sunnet.dir/src/SocketWorker.cpp.o: CMakeFiles/sunnet.dir/flags.make
CMakeFiles/sunnet.dir/src/SocketWorker.cpp.o: ../src/SocketWorker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/cc_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sunnet.dir/src/SocketWorker.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sunnet.dir/src/SocketWorker.cpp.o -c /root/cc_project/src/SocketWorker.cpp

CMakeFiles/sunnet.dir/src/SocketWorker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sunnet.dir/src/SocketWorker.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/cc_project/src/SocketWorker.cpp > CMakeFiles/sunnet.dir/src/SocketWorker.cpp.i

CMakeFiles/sunnet.dir/src/SocketWorker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sunnet.dir/src/SocketWorker.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/cc_project/src/SocketWorker.cpp -o CMakeFiles/sunnet.dir/src/SocketWorker.cpp.s

CMakeFiles/sunnet.dir/src/SocketWorker.cpp.o.requires:

.PHONY : CMakeFiles/sunnet.dir/src/SocketWorker.cpp.o.requires

CMakeFiles/sunnet.dir/src/SocketWorker.cpp.o.provides: CMakeFiles/sunnet.dir/src/SocketWorker.cpp.o.requires
	$(MAKE) -f CMakeFiles/sunnet.dir/build.make CMakeFiles/sunnet.dir/src/SocketWorker.cpp.o.provides.build
.PHONY : CMakeFiles/sunnet.dir/src/SocketWorker.cpp.o.provides

CMakeFiles/sunnet.dir/src/SocketWorker.cpp.o.provides.build: CMakeFiles/sunnet.dir/src/SocketWorker.cpp.o


CMakeFiles/sunnet.dir/src/Sunnet.cpp.o: CMakeFiles/sunnet.dir/flags.make
CMakeFiles/sunnet.dir/src/Sunnet.cpp.o: ../src/Sunnet.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/cc_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/sunnet.dir/src/Sunnet.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sunnet.dir/src/Sunnet.cpp.o -c /root/cc_project/src/Sunnet.cpp

CMakeFiles/sunnet.dir/src/Sunnet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sunnet.dir/src/Sunnet.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/cc_project/src/Sunnet.cpp > CMakeFiles/sunnet.dir/src/Sunnet.cpp.i

CMakeFiles/sunnet.dir/src/Sunnet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sunnet.dir/src/Sunnet.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/cc_project/src/Sunnet.cpp -o CMakeFiles/sunnet.dir/src/Sunnet.cpp.s

CMakeFiles/sunnet.dir/src/Sunnet.cpp.o.requires:

.PHONY : CMakeFiles/sunnet.dir/src/Sunnet.cpp.o.requires

CMakeFiles/sunnet.dir/src/Sunnet.cpp.o.provides: CMakeFiles/sunnet.dir/src/Sunnet.cpp.o.requires
	$(MAKE) -f CMakeFiles/sunnet.dir/build.make CMakeFiles/sunnet.dir/src/Sunnet.cpp.o.provides.build
.PHONY : CMakeFiles/sunnet.dir/src/Sunnet.cpp.o.provides

CMakeFiles/sunnet.dir/src/Sunnet.cpp.o.provides.build: CMakeFiles/sunnet.dir/src/Sunnet.cpp.o


CMakeFiles/sunnet.dir/src/Worker.cpp.o: CMakeFiles/sunnet.dir/flags.make
CMakeFiles/sunnet.dir/src/Worker.cpp.o: ../src/Worker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/cc_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/sunnet.dir/src/Worker.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sunnet.dir/src/Worker.cpp.o -c /root/cc_project/src/Worker.cpp

CMakeFiles/sunnet.dir/src/Worker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sunnet.dir/src/Worker.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/cc_project/src/Worker.cpp > CMakeFiles/sunnet.dir/src/Worker.cpp.i

CMakeFiles/sunnet.dir/src/Worker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sunnet.dir/src/Worker.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/cc_project/src/Worker.cpp -o CMakeFiles/sunnet.dir/src/Worker.cpp.s

CMakeFiles/sunnet.dir/src/Worker.cpp.o.requires:

.PHONY : CMakeFiles/sunnet.dir/src/Worker.cpp.o.requires

CMakeFiles/sunnet.dir/src/Worker.cpp.o.provides: CMakeFiles/sunnet.dir/src/Worker.cpp.o.requires
	$(MAKE) -f CMakeFiles/sunnet.dir/build.make CMakeFiles/sunnet.dir/src/Worker.cpp.o.provides.build
.PHONY : CMakeFiles/sunnet.dir/src/Worker.cpp.o.provides

CMakeFiles/sunnet.dir/src/Worker.cpp.o.provides.build: CMakeFiles/sunnet.dir/src/Worker.cpp.o


CMakeFiles/sunnet.dir/src/cat.cpp.o: CMakeFiles/sunnet.dir/flags.make
CMakeFiles/sunnet.dir/src/cat.cpp.o: ../src/cat.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/cc_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/sunnet.dir/src/cat.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sunnet.dir/src/cat.cpp.o -c /root/cc_project/src/cat.cpp

CMakeFiles/sunnet.dir/src/cat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sunnet.dir/src/cat.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/cc_project/src/cat.cpp > CMakeFiles/sunnet.dir/src/cat.cpp.i

CMakeFiles/sunnet.dir/src/cat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sunnet.dir/src/cat.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/cc_project/src/cat.cpp -o CMakeFiles/sunnet.dir/src/cat.cpp.s

CMakeFiles/sunnet.dir/src/cat.cpp.o.requires:

.PHONY : CMakeFiles/sunnet.dir/src/cat.cpp.o.requires

CMakeFiles/sunnet.dir/src/cat.cpp.o.provides: CMakeFiles/sunnet.dir/src/cat.cpp.o.requires
	$(MAKE) -f CMakeFiles/sunnet.dir/build.make CMakeFiles/sunnet.dir/src/cat.cpp.o.provides.build
.PHONY : CMakeFiles/sunnet.dir/src/cat.cpp.o.provides

CMakeFiles/sunnet.dir/src/cat.cpp.o.provides.build: CMakeFiles/sunnet.dir/src/cat.cpp.o


CMakeFiles/sunnet.dir/src/main.cpp.o: CMakeFiles/sunnet.dir/flags.make
CMakeFiles/sunnet.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/cc_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/sunnet.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sunnet.dir/src/main.cpp.o -c /root/cc_project/src/main.cpp

CMakeFiles/sunnet.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sunnet.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/cc_project/src/main.cpp > CMakeFiles/sunnet.dir/src/main.cpp.i

CMakeFiles/sunnet.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sunnet.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/cc_project/src/main.cpp -o CMakeFiles/sunnet.dir/src/main.cpp.s

CMakeFiles/sunnet.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/sunnet.dir/src/main.cpp.o.requires

CMakeFiles/sunnet.dir/src/main.cpp.o.provides: CMakeFiles/sunnet.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/sunnet.dir/build.make CMakeFiles/sunnet.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/sunnet.dir/src/main.cpp.o.provides

CMakeFiles/sunnet.dir/src/main.cpp.o.provides.build: CMakeFiles/sunnet.dir/src/main.cpp.o


CMakeFiles/sunnet.dir/src/service.cpp.o: CMakeFiles/sunnet.dir/flags.make
CMakeFiles/sunnet.dir/src/service.cpp.o: ../src/service.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/cc_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/sunnet.dir/src/service.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sunnet.dir/src/service.cpp.o -c /root/cc_project/src/service.cpp

CMakeFiles/sunnet.dir/src/service.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sunnet.dir/src/service.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/cc_project/src/service.cpp > CMakeFiles/sunnet.dir/src/service.cpp.i

CMakeFiles/sunnet.dir/src/service.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sunnet.dir/src/service.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/cc_project/src/service.cpp -o CMakeFiles/sunnet.dir/src/service.cpp.s

CMakeFiles/sunnet.dir/src/service.cpp.o.requires:

.PHONY : CMakeFiles/sunnet.dir/src/service.cpp.o.requires

CMakeFiles/sunnet.dir/src/service.cpp.o.provides: CMakeFiles/sunnet.dir/src/service.cpp.o.requires
	$(MAKE) -f CMakeFiles/sunnet.dir/build.make CMakeFiles/sunnet.dir/src/service.cpp.o.provides.build
.PHONY : CMakeFiles/sunnet.dir/src/service.cpp.o.provides

CMakeFiles/sunnet.dir/src/service.cpp.o.provides.build: CMakeFiles/sunnet.dir/src/service.cpp.o


# Object files for target sunnet
sunnet_OBJECTS = \
"CMakeFiles/sunnet.dir/src/LuaAPI.cpp.o" \
"CMakeFiles/sunnet.dir/src/SocketWorker.cpp.o" \
"CMakeFiles/sunnet.dir/src/Sunnet.cpp.o" \
"CMakeFiles/sunnet.dir/src/Worker.cpp.o" \
"CMakeFiles/sunnet.dir/src/cat.cpp.o" \
"CMakeFiles/sunnet.dir/src/main.cpp.o" \
"CMakeFiles/sunnet.dir/src/service.cpp.o"

# External object files for target sunnet
sunnet_EXTERNAL_OBJECTS =

sunnet: CMakeFiles/sunnet.dir/src/LuaAPI.cpp.o
sunnet: CMakeFiles/sunnet.dir/src/SocketWorker.cpp.o
sunnet: CMakeFiles/sunnet.dir/src/Sunnet.cpp.o
sunnet: CMakeFiles/sunnet.dir/src/Worker.cpp.o
sunnet: CMakeFiles/sunnet.dir/src/cat.cpp.o
sunnet: CMakeFiles/sunnet.dir/src/main.cpp.o
sunnet: CMakeFiles/sunnet.dir/src/service.cpp.o
sunnet: CMakeFiles/sunnet.dir/build.make
sunnet: CMakeFiles/sunnet.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/cc_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable sunnet"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sunnet.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sunnet.dir/build: sunnet

.PHONY : CMakeFiles/sunnet.dir/build

CMakeFiles/sunnet.dir/requires: CMakeFiles/sunnet.dir/src/LuaAPI.cpp.o.requires
CMakeFiles/sunnet.dir/requires: CMakeFiles/sunnet.dir/src/SocketWorker.cpp.o.requires
CMakeFiles/sunnet.dir/requires: CMakeFiles/sunnet.dir/src/Sunnet.cpp.o.requires
CMakeFiles/sunnet.dir/requires: CMakeFiles/sunnet.dir/src/Worker.cpp.o.requires
CMakeFiles/sunnet.dir/requires: CMakeFiles/sunnet.dir/src/cat.cpp.o.requires
CMakeFiles/sunnet.dir/requires: CMakeFiles/sunnet.dir/src/main.cpp.o.requires
CMakeFiles/sunnet.dir/requires: CMakeFiles/sunnet.dir/src/service.cpp.o.requires

.PHONY : CMakeFiles/sunnet.dir/requires

CMakeFiles/sunnet.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sunnet.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sunnet.dir/clean

CMakeFiles/sunnet.dir/depend:
	cd /root/cc_project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/cc_project /root/cc_project /root/cc_project/build /root/cc_project/build /root/cc_project/build/CMakeFiles/sunnet.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sunnet.dir/depend

