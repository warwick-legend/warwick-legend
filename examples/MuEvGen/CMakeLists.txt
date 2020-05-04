# - Basic CMake setup
# Check version meets your requirements
# Declare project, which will configure compiler for us
cmake_minimum_required(VERSION 2.8)
project(MuEvGen)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#Executable
add_executable(mugen.exe muongenerator.cpp)


