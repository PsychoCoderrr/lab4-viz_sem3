# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/vitalijkoldasev/Desktop/laboratories_3_sem/try_qt/try_qt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/vitalijkoldasev/Desktop/laboratories_3_sem/try_qt/try_qt/build

# Utility rule file for GraphEditor_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/GraphEditor_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/GraphEditor_autogen.dir/progress.make

CMakeFiles/GraphEditor_autogen: GraphEditor_autogen/timestamp

GraphEditor_autogen/timestamp: /opt/homebrew/Cellar/qt/6.7.3/share/qt/libexec/moc
GraphEditor_autogen/timestamp: /opt/homebrew/Cellar/qt/6.7.3/share/qt/libexec/uic
GraphEditor_autogen/timestamp: CMakeFiles/GraphEditor_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/vitalijkoldasev/Desktop/laboratories_3_sem/try_qt/try_qt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target GraphEditor"
	/opt/homebrew/bin/cmake -E cmake_autogen /Users/vitalijkoldasev/Desktop/laboratories_3_sem/try_qt/try_qt/build/CMakeFiles/GraphEditor_autogen.dir/AutogenInfo.json Debug
	/opt/homebrew/bin/cmake -E touch /Users/vitalijkoldasev/Desktop/laboratories_3_sem/try_qt/try_qt/build/GraphEditor_autogen/timestamp

CMakeFiles/GraphEditor_autogen.dir/codegen:
.PHONY : CMakeFiles/GraphEditor_autogen.dir/codegen

GraphEditor_autogen: CMakeFiles/GraphEditor_autogen
GraphEditor_autogen: GraphEditor_autogen/timestamp
GraphEditor_autogen: CMakeFiles/GraphEditor_autogen.dir/build.make
.PHONY : GraphEditor_autogen

# Rule to build all files generated by this target.
CMakeFiles/GraphEditor_autogen.dir/build: GraphEditor_autogen
.PHONY : CMakeFiles/GraphEditor_autogen.dir/build

CMakeFiles/GraphEditor_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GraphEditor_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GraphEditor_autogen.dir/clean

CMakeFiles/GraphEditor_autogen.dir/depend:
	cd /Users/vitalijkoldasev/Desktop/laboratories_3_sem/try_qt/try_qt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/vitalijkoldasev/Desktop/laboratories_3_sem/try_qt/try_qt /Users/vitalijkoldasev/Desktop/laboratories_3_sem/try_qt/try_qt /Users/vitalijkoldasev/Desktop/laboratories_3_sem/try_qt/try_qt/build /Users/vitalijkoldasev/Desktop/laboratories_3_sem/try_qt/try_qt/build /Users/vitalijkoldasev/Desktop/laboratories_3_sem/try_qt/try_qt/build/CMakeFiles/GraphEditor_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/GraphEditor_autogen.dir/depend

