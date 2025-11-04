#include "Image.hpp"

Image::Image()
    : data(nullptr), width(0), height(0), channels(0) {}

Image::Image(unsigned char* data, int width, int height, int channels)
    : data(data), width(width), height(height), channels(channels) {}