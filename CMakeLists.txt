# Version check
cmake_minimum_required (VERSION 3.0)

# Project
project(SimpleJSON)

# Add files
file(GLOB sources "parse/*.cpp" "stringify/*.cpp" "utility/*.cpp")

# Add library
add_library(SimpleJSON STATIC ${sources})

# Compiler Options
target_compile_options(SimpleJSON PRIVATE -fexceptions -std=c++14 -O3 -Wall -pedantic-errors -pedantic)