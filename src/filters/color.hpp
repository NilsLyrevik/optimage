#ifndef COLOR_HPP
#define COLOR_HPP

#include "../image.hpp"

Image Sepia(Image& img);
Image natural_gray(Image& img);
Image hue_shift(Image& img,float angle);

#endif