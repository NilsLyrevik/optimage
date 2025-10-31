cmake_minimum_required(VERSION 3.10)
project(optimage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatically gather all .cpp files in src/
file(GLOB_RECURSE SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/tools/stb_image
)

# Create the executable with all source files
add_executable(optimage
    main.cpp
    ${SRC_FILES}
)

# Optional: Ensure an output directory exists (for saved images, etc.)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)
