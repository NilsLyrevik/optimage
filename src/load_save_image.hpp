#pragma once
/**
 * @file load_save_image.hpp
 * @brief Helper functions for loading and saving images using stb_image.
 *
 * Provides utilities for:
 *  - Creating directories
 *  - Auto-naming output files based on date
 *  - Loading images from disk
 *  - Saving images with automatic naming and format handling
 */

#include <string>
#include <filesystem>

// stb forward declarations — no need to include implementations here
// Include "stb_image.h" and "stb_image_write.h" in the .cpp file only.

namespace optimage {

/**
 * @brief Creates a directory if it does not already exist.
 *
 * @param dir_name The name or path of the directory to create.
 */
void createdir(const std::string& dir_name);

/**
 * @brief Generates a unique output filename based on today's date.
 *
 * Example outputs:
 *   - output/2025_10_31.png
 *   - output/2025_10_31_1.png
 *
 * @param output_dir Directory where the file should be saved.
 * @param extension File extension (e.g., ".jpg" or ".png").
 * @return The full path to a unique filename.
 */
std::string generate_output_filename(const std::string& output_dir,
                                     const std::string& extension = ".png");

/**
 * @brief Loads an image from a file path using stb_image.
 *
 * @param filepath Path to the image file.
 * @param width Output variable for image width.
 * @param height Output variable for image height.
 * @param channels Output variable for number of channels.
 * @return Pointer to raw image data, or nullptr on failure.
 * @note Must call `stbi_image_free()` after use.
 */
unsigned char* load_image(const std::string& filepath,
                          int& width, int& height, int& channels);

/**
 * @brief Saves an image to an automatically named file in the "output" directory.
 *
 * @param data Pointer to image data.
 * @param width Image width.
 * @param height Image height.
 * @param channels Number of color channels.
 * @return true if successful, false otherwise.
 */
bool save_image(unsigned char* data, int width, int height, int channels);

} // namespace optimage
