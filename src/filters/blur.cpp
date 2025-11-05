#include "../image.hpp"
#include <algorithm> 
#include <cmath>
#include <random>

/*
Why is this optimized:
    -> Uses no std:vector (no dynamic allocation. therefore less jumps onto heap and fastter access)
    -> Checks rows first, so that when we fetch to the L1 cache we get less cache misses.
    -> each pixel has a small fixed size buffer to use. making sorting faster aswell as smaller array to keept track of each pixels  neightborhood;
Reccomendation:
    -> Use with lower radius as incresing it increases nested loops by alot. recomended range for speed 3 - 5 pixels!!!
*/

Image circular_median_blur(const Image& img, int radius) {
    const int maxSamples = (2 * radius + 1) * (2 * radius + 1);
    unsigned char* blurred_data = (unsigned char*)malloc(img.width * img.height * img.channels);

    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            // Fixed-size buffers
            unsigned char red[maxSamples];
            unsigned char green[maxSamples];
            unsigned char blue[maxSamples];
            int count = 0;

            for (int dy = -radius; dy <= radius; ++dy) {
                for (int dx = -radius; dx <= radius; ++dx) {
                    int nx = x + dx;
                    int ny = y + dy;

                    // Bounds check
                    if (nx < 0 || ny < 0 || nx >= img.width || ny >= img.height)
                        continue;

                    // Circle check
                    if (dx * dx + dy * dy > radius * radius)
                        continue;

                    int idx = (ny * img.width + nx) * img.channels;
                    red[count]   = img.data[idx];
                    green[count] = img.data[idx + 1];
                    blue[count]  = img.data[idx + 2];
                    ++count;
                }
            }

            // Sort only used portion
            std::sort(red, red + count);
            std::sort(green, green + count);
            std::sort(blue, blue + count);

            int out_idx = (y * img.width + x) * img.channels;
            blurred_data[out_idx]     = red[count / 2];
            blurred_data[out_idx + 1] = green[count / 2];
            blurred_data[out_idx + 2] = blue[count / 2];

            // Preserve alpha if present
            if (img.channels == 4)
                blurred_data[out_idx + 3] = img.data[out_idx + 3];
        }
    }

    return Image(blurred_data, img.width, img.height, img.channels);
}


// Maybe this one can be more eficient in some way?
/*
int clamp(int low, int high, int num){
    if (num < low) return low;
    if (num > high) return high;
    return num;
}

*/
//Branchless version (maybe faster in clock cycles but old version above still very fast)
int clamp(int low, int high, int num){
    return (num < low) ? low : (num > high) ? high : num;
}

/*
Why it's fast.
    -> each pixel only visited once
    -> no temporary buffers. we malloc once!

Possible improvements:
    -> Make it parallel.
*/
Image random_blur_v1(const Image& img){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-1, 1);

    unsigned char* blurred_data = (unsigned char*)malloc(img.width * img.height * img.channels);

    for (int y = 0; y < img.height; ++y){
        for (int x = 0; x < img.width; ++x){
            int randx = dist(gen);
            int randy = dist(gen);

            int idx = (y * img.width + x) * img.channels;
            int rand_idx = (clamp(0, img.height - 1, y + randy) * img.width +
                            clamp(0, img.width - 1, x + randx)) * img.channels;


            blurred_data[idx]     = img.data[rand_idx]; 
            blurred_data[idx + 1] = img.data[rand_idx + 1]; 
            blurred_data[idx + 2] = img.data[rand_idx + 2]; 

            if (img.channels == 4)
                blurred_data[idx + 3] = img.data[rand_idx + 3]; 
        }
    }

    return Image(blurred_data, img.width, img.height, img.channels);
}

Image color_average_blur(const Image& img, int dimension){

    unsigned char* blurred_data = (unsigned char*)malloc(img.width * img.height * img.channels);
    int vector_size = dimension * dimension;
    for (int y = 0; y < img.height; ++y){
        for (int x = 0; x < img.width; ++x){

            unsigned char red[vector_size];
            unsigned char green[vector_size];
            unsigned char blue[vector_size];

            int idx = (y * img.width + x) * img.channels;
            int index = 0;
            for (int dy = y - (dimension / 2); dy <= y + (dimension / 2) ; ++dy){
                for (int dx = x - (dimension / 2); dx <= x + (dimension / 2) ; ++dx){
                    //clamp y
                    int temp_dy = clamp(0,img.height - 1,dy);
                    //clamp x
                    int temp_dx = clamp(0,img.width - 1,dx);

                    int d_idx = (temp_dy * img.width + temp_dx) * img.channels;
                    red[index] = img.data[d_idx];
                    green[index] = img.data[d_idx + 1];
                    blue[index] = img.data[d_idx + 2];
                    ++index;
                }
            }
            int red_i = 0,green_i = 0,blue_i = 0;

            for (int i = 0; i < vector_size; ++i){
                red_i += (int)red[i];
                green_i += (int)green[i];
                blue_i += (int)blue[i];
            }

            red_i = red_i/vector_size;
            green_i = green_i/vector_size;
            blue_i = blue_i/vector_size;

            blurred_data[idx]     = clamp(0,255,red_i); 
            blurred_data[idx + 1] = clamp(0,255,green_i); 
            blurred_data[idx + 2] = clamp(0,255,blue_i); 

            if (img.channels == 4)
                blurred_data[idx + 3] = img.data[idx + 3]; 
        }
    }

    return Image(blurred_data, img.width, img.height, img.channels);
}
