cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Morse LANGUAGES C)

# Collect all .c files
file(GLOB SOURCES "*.c")

# Add the executable
add_executable(morse ${SOURCES})
