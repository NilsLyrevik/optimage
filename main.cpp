#include <iostream>
#include <string>

// Personal includes
#include "src/load_save_image.hpp"

using namespace std;

void print_help() {
    cout << "Usage: <PATH TO INPUT IMAGE> <FLAG>\n\n"
         << "Flags:\n"
         << "  -h, --help  |  Show this help message\n"
         << "  -s, --save  |  Only saves current PNG to a JPG with no modification\n";
}

int main(int argc, char* argv[]) {
    int width, height, channels;

    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input_image> <flag>" << endl;
        return 1;
    }

    string flag = argv[2];
    if (flag == "-h" || flag == "--help") {
        print_help();
        return 0;
    }
    bool skipfilter = false;
    if (flag == "-s" || flag == "--save"){
      cout << "No filter choosen, only saving picture as JPG" << endl;
      skipfilter = true;
    }

    unsigned char* data = load_image(argv[1], width, height, channels);
    if (!data) {
        cerr << "Failed to load image: " << argv[1] << endl;
        return 1;
    }

    if (!skipfilter){
      cout << "filter choosen : " << endl; // FIX THIS SO THAT IS SAYS WHICH FILTER IS CHOOSEN!!!!

       // IMAGE PROCESSING LOGIC GOES HERE
       
    }

    if (!save_image(data, width, height, channels)) {
        cerr << "Error while saving image :/" << endl;
        return 1;
    }

    cout << "Image saved successfully!" << endl;
    return 0;
}
