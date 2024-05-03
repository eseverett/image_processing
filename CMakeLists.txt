cmake_minimum_required(VERSION 3.10) 
project(run_process LANGUAGES CXX) 

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(run_process src/main.cpp src/process_paths.cpp src/image_attributes.cpp)  

# Include the header files
include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_TOOLCHAIN_FILE C:/Users/ejsev/Documents/vcpkg/scripts/buildsystems/vcpkg.cmake)

# Find and link Boost
find_package(Boost REQUIRED)
if(Boost_FOUND)
    target_include_directories(run_process PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(run_process PRIVATE ${Boost_LIBRARIES})
endif()

# Find and link HDF5
find_package(HDF5 REQUIRED COMPONENTS C HL)
if(HDF5_FOUND)
    target_include_directories(run_process PRIVATE ${HDF5_INCLUDE_DIRS})
    target_link_libraries(run_process PRIVATE ${HDF5_LIBRARIES} ${HDF5_HL_LIBRARIES})
endif()

# Compiler-specific options
if(MSVC)
    target_compile_options(run_process PRIVATE /W4)
else()
    target_compile_options(run_process PRIVATE -Wall -Wextra -pedantic)
endif()



