# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyProject VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add executable target
add_executable(Engine
    src/main.cpp
    src/ExecutionEngine.cpp
    src/Ruleset.cpp
)