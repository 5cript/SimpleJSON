# Version check
cmake_minimum_required (VERSION 3.8)

if ("${CMAKE_CXX_STANDARD}" LESS 11)
	message(FATAL_ERROR "Library cannot be compiled with at least C++11 support")	
endif()

if(NOT "${CMAKE_CXX_STANDARD}")
	set(CMAKE_CXX_STANDARD 17)
endif()

# Project
project(SimpleJSON)

# Add files
file(GLOB sources "parse/*.cpp" "stringify/*.cpp" "utility/*.cpp")

# Add library
add_library(SimpleJSON STATIC ${sources})

# Compiler Options
set(DEBUG_OPTIONS "-fexceptions -g -Wall -pedantic-errors -pedantic")
set(RELEASE_OPTIONS "-fexceptions -O3 -Wall -pedantic-errors -pedantic")
target_compile_options(SimpleJSON PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>")
target_compile_options(SimpleJSON PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")