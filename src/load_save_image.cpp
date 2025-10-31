#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;

/*
 * creates a dir. thats it hehe
 */
void createdir(const string& dir_name) {
    try {
        if (!fs::exists(dir_name)) {
            fs::create_directory(dir_name);
            cout << "Created directory: " << dir_name << endl;
        }
    } catch (const fs::filesystem_error& e) {
        cerr << "Error creating directory: " << e.what() << endl;
    }
}

/*
 * function to keep the output file tidy and handle multiple saves if necessary.
 */
string generate_output_filename(const string& output_dir, const string& extension = ".png") {
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);
    tm local_tm{};
#ifdef _WIN32
    localtime_s(&local_tm, &t);
#else
    localtime_r(&t, &local_tm);
#endif

    stringstream date_ss;
    date_ss << put_time(&local_tm, "%Y_%m_%d");

    string base_name = date_ss.str();
    string filename = base_name + extension;
    string full_path = output_dir + "/" + filename;

    int counter = 1;
    while (fs::exists(full_path)) {
        filename = base_name + "_" + to_string(counter) + extension;
        full_path = output_dir + "/" + filename;
        counter++;
    }

    return full_path;
}

/*
 * simple function to load image from file path
 */
unsigned char* load_image(const string& filepath, int& width, int& height, int& channels) {
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
    if (!data) {
        cerr << "Failed to load image at: " << filepath << endl;
        return nullptr;
    }

    cout << "Loaded image: " << filepath << endl;
    cout << "Width: " << width << ", Height: " << height << ", Channels: " << channels << endl;

    return data;
}

/*
 * saves an image. uses some helpers to keep things tidy.
 */
bool save_image(unsigned char* data, int width, int height, int channels) {
    string output_dir = "output";
    createdir(output_dir);

    string output_filepath = generate_output_filename(output_dir, ".jpg");

    if (!stbi_write_jpg(output_filepath.c_str(), width, height, channels, data, 90)) {
        cerr << "Failed to save image at: " << output_filepath << endl;
        stbi_image_free(data);
        return false;
    }

    cout << "Saved image: " << output_filepath << endl;
    stbi_image_free(data);
    return true;
}