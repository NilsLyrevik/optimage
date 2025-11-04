cmake_minimum_required(VERSION 3.10)
project(optimage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include all .cpp files from src automatically
file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(optimage
    main.cpp
    ${SRC_FILES}
)

# Include headers in src/
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/tools)
