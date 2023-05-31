cmake_minimum_required(VERSION 3.25)
project(InstaBrute)

set(CMAKE_CXX_STANDARD 17)

# Set the path to the SDL2 library
set(SDL2_INCLUDE_DIR "C:/Program Files/JetBrains/CLion 2023.1.2/bin/mingw/include/SDL2")
set(SDL2_LIBRARY_DIR "C:/Program Files/JetBrains/CLion 2023.1.2/bin/mingw/lib")

# Add the SDL2 include directory
include_directories(${SDL2_INCLUDE_DIR})

# Add the SDL2 library directory
link_directories(${SDL2_LIBRARY_DIR})

# Add your source files
add_executable(InstaBrute main.cpp main.h)

# Link against the SDL2 libraries
target_link_libraries(InstaBrute PRIVATE SDL2 SDL2main)
