cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Morse LANGUAGES C)

# Collect all .c files
file(GLOB SOURCES "*.c")

# Add the executable
add_executable(morse ${SOURCES})

# Set runtime output directory based on the configuration
if(MSVC)  # If building with Visual Studio
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()
