#ifndef BLUR_HPP
#define BLUR_HPP

#include "../image.hpp"

Image circular_median_blur(const Image& img, int radius);
Image random_blur_v1(const Image& img);

#endif
