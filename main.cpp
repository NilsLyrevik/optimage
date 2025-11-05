#include <iostream>
#include <string>

// Personal includes
#include "src/load_save_image.hpp"
#include "src/image.hpp"
#include "src/filters/blur.hpp"

using namespace std;

void print_help() {
    cout << "Usage: optimage <PATH TO INPUT IMAGE> <FLAG>\n\n"
         << "Flags:\n"
         << "  -h, --help            Show this help message\n"
         << "  -s, --save            Only saves current image (no modification)\n"
         << "  -cb, --circularblur   Apply circular median blur\n"
         << "  -v1, --randomblur   Apply random blur (Nils edition v1)\n"
         << "  -v2, --colormblur   Apply a color median blur (Nils edition v2)\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input_image> <flag>" << endl;
        return 1;
    }

    string input_path = argv[1];
    string flag = argv[2];

    if (flag == "-h" || flag == "--help") {
        print_help();
        return 0;
    }

    int width, height, channels;
    unsigned char* data = load_image(input_path, width, height, channels);
    if (!data) {
        cerr << "Failed to load image: " << input_path << endl;
        return 1;
    }

    Image img(data, width, height, channels);
    Image output = img; // Default: same as input

    if (flag == "-s" || flag == "--save") {
        cout << "No filter chosen, saving image as-is." << endl;
    }
    else if (flag == "-cb" || flag == "--circularblur") {
        cout << "Applying circular median blur..." << endl;
        output = circular_median_blur(img, 3); // You can tweak radius
    }
    else if (flag == "-v1" || flag == "--randomblur") {
        cout << "Applying random blur... (Nils Edition v1)" << endl;
        output = random_blur_v1(img);
    }
    else if (flag == "-v2" || flag == "--colormblur") {
        cout << "Applying random blur... (Nils Edition v2)" << endl;
        output = color_median_blur(img,5);
    }
    else {
        cerr << "Unknown flag: " << flag << endl;
        print_help();
        free(data);
        return 1;
    }

    if (!save_image(output.data, output.width, output.height, output.channels, flag)) {
        cerr << "Error while saving image :/" << endl;
        free(data);
        return 1;
    }

    cout << "Image saved successfully!" << endl;
    free(data);
    return 0;
}
