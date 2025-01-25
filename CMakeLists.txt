cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Morse LANGUAGES C)

# Collect all .c files
file(GLOB SOURCES "*.c")

# Add the executable
add_executable(morse ${SOURCES})

if(MSVC)
    # Use /W4 for high warning levels in MSVC (or any preferred level)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    # For GCC/Clang, use -Wall -Werror
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror)
endif()

