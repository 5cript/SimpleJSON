# Version check
cmake_minimum_required (VERSION 3.8)

if(NOT "${CMAKE_CXX_STANDARD}")
	set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
  if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
  endif()
endif()

# Project
project(SimpleJSON)

# Add files
file(GLOB sources "parse/*.cpp" "stringify/*.cpp" "utility/*.cpp")

# Add library
add_library(SimpleJSON STATIC ${sources})

# Compiler Options
set(DEBUG_OPTIONS -fexceptions -g -Wall -pedantic-errors -pedantic)
set(RELEASE_OPTIONS -fexceptions -O3 -Wall -pedantic-errors -pedantic)
target_compile_options(SimpleJSON PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>")
target_compile_options(SimpleJSON PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")