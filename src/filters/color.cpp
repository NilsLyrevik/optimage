#include "../image.hpp"

//HELPERS
float f_clamp(float low, float high, float num){
    return (low > num) ? low : (high < num) ? high : num;
}

int i_clamp(int low, int high, int num){
    return (low > num) ? low : (high < num) ? high : num;
}
// IMAGE COLORING FUNCTIONS

Image Sepia(Image& img){

    unsigned char* colored_data = (unsigned char*)malloc(img.width * img.height * img.channels);

    for(int y = 0; y < img.height; ++y){
        for (int x = 0; x < img.width; ++x){
            float red = 0.0, green = 0.0, blue = 0.0;
            int idx = (y * img.width + x) * img.channels;

            red = f_clamp(0.0, 255.0, img.data[idx] * 0.393 + img.data[idx + 1] * 0.769 + img.data[idx + 2] * 0.189);
            green = f_clamp(0.0, 255.0,img.data[idx] * 0.349 + img.data[idx + 1] * 0.686 + img.data[idx + 2] * 0.168);
            blue = f_clamp(0.0, 255.0,img.data[idx] * 0.272 + img.data[idx + 1] * 0.534 + img.data[idx + 2] * 0.131);

            colored_data[idx]     = (unsigned char)red;
            colored_data[idx + 1] = (unsigned char)green;
            colored_data[idx + 2] = (unsigned char)blue;    
            
            if (img.channels == 4){
                colored_data[idx + 3] = img.data[idx + 3];
            }
        }
    }
    return Image(colored_data, img.width, img.height, img.channels);
}

/*
Implemnted using ointer arithemitic!!!

Alot cooler and shorter code. however a little bit less readble.
*/
Image natural_gray(Image& img){
    unsigned char* gray_data = (unsigned char*)malloc(img.width * img.height * img.channels);
    unsigned char* src = img.data;
    unsigned char* dst = gray_data;
    int pixels = img.width * img.height;

    for (int i = 0; i < pixels; ++i) {
        float gray = src[0]*0.2126f + src[1]*0.7152f + src[2]*0.0722f;
        unsigned char g = (unsigned char)gray;

        dst[0] = dst[1] = dst[2] = g;
        if (img.channels == 4)
            dst[3] = src[3];

        src += img.channels; // move to next pixel
        dst += img.channels;
    }
    return Image(gray_data, img.width, img.height, img.channels);
}