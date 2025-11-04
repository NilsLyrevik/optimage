#pragma once
#include <string>

class Image {
public:
    unsigned char* data;
    int width;
    int height;
    int channels;

    Image();  // Default constructor, only fills zeroes/nullptr
    Image(unsigned char* data, int width, int height, int channels);
};