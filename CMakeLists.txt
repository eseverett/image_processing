cmake_minimum_required(VERSION 3.10)  # Adjust this line according to your CMake version
project(run_process)  # Name your project

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the directories where to search for headers
include_directories(include)

# Add the executable
add_executable(run_process src/main.cpp src/process_paths.cpp)  # Specify the correct path to main.cpp

# Find Boost
find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(run_process ${Boost_LIBRARIES})
endif()

# Find HDF5
find_package(HDF5 REQUIRED COMPONENTS C HL)
if(HDF5_FOUND)
    include_directories(${HDF5_INCLUDE_DIRS})
    target_link_libraries(run_process ${HDF5_LIBRARIES} ${HDF5_HL_LIBRARIES})
endif()

# Compiler-specific options
if(MSVC)
    target_compile_options(run_process PRIVATE /W4)
else()
    target_compile_options(run_process PRIVATE -Wall -Wextra -pedantic)
endif()
