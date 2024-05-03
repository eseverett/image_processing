cmake_minimum_required(VERSION 3.10)  # Adjust this line according to your CMake version

project(run_process)  # Name your project

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(run_process src/main.cpp)  # Specify the correct path to main.cpp

# Check if the compiler is MSVC and set the compile options accordingly
if(MSVC)
    target_compile_options(run_process PRIVATE /W4)
else()
    target_compile_options(run_process PRIVATE -Wall -Wextra -pedantic)
endif()
