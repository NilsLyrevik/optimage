#optimage
##Optimizing image editing

##Overview
optimage is a C/C++ project focused on exploring techniques to optimize image processing workflows — especially around memory usage, performance, and clean architecture. While this repository began as a learning exercise, it also serves as a demonstration of interest and skill in the domain of image editing optimization.

##Repository structure
/output               # Generated output or binaries
/src                  # Source code (C / C++)
/tools/stb_image      # Third-party helpers for image loading, etc.
/CMakeLists.txt       # Build configuration
/main.cpp             # Main entry point
README.md             # This file
.gitignore

##Key features and focus
- Memory optimization: exploring how images are stored, manipulated, and kept efficient
- Performance awareness: leveraging C/C++ to achieve minimal overhead and close-to-hardware performance
- Clean build system: using CMake for portability and dependency management
- Lightweight image loading via stb_image or similar libraries

##Getting started

##Prerequisites
- A C/C++ compiler (e.g., GCC, Clang, MSVC)
- CMake (for generating build files)
- Standard libraries for image loading (included in /tools/stb_image)

##Build instructions
git clone https://github.com/NilsLyrevik/optimage.git
cd optimage
mkdir build && cd build
cmake ..
make

##Running
After building, you’ll have an executable in build/ (or output/). Run it with the appropriate command-line arguments, for example:
./optimage input.png output.png

##Use cases
- Experimenting with low-level image editing pipelines
- Prototyping memory-efficient image operations in C/C++
- Understanding how performance-oriented image workflows differ from high-level approaches

##Why this matters
Image processing is used in nearly every domain — from games to mobile apps to machine learning. However, performance and memory costs are often overlooked. This project demonstrates how efficient image editing can be achieved at the low level, providing insight into how pixels are loaded, processed, and stored.

##Roadmap
##Potential future improvements:
- Benchmark suite comparing performance across formats and sizes
- GPU/CUDA or OpenCL acceleration
- Command-line interface or lightweight GUI for batch processing
- Unit tests and continuous integration setup
