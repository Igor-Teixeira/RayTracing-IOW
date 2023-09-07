#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct PixelData
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

static void WritePPM(const std::string& filename, unsigned int width,
    unsigned int height, const std::vector<PixelData>& pixels)
{
    std::ofstream ppmFile{filename, std::ios::binary};

    if (!ppmFile.is_open()) {
        std::cerr << "Failed to open PPM file for writing: [" << filename << "]" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    ppmFile << "P3\n" << width << " " << height << "\n255\n";

    for (unsigned int j = 0; j < height; ++j) {
        for (unsigned int i = 0; i < width; ++i) {
            const auto& pixel = pixels[j * width + i];

            ppmFile <<
                (unsigned int)pixel.r << " " <<
                (unsigned int)pixel.g << " " <<
                (unsigned int)pixel.b << "\n";
        }
    }
}

int main()
{
    constexpr unsigned int IMAGE_WIDTH = 256;
    constexpr unsigned int IMAGE_HEIGHT = 256;

    std::vector<PixelData> pixels(IMAGE_WIDTH * IMAGE_HEIGHT);

    for (unsigned int j = 0; j < IMAGE_HEIGHT; ++j) {
        for (unsigned int i = 0; i < IMAGE_WIDTH; ++i) {
            const double r = double(i) / (IMAGE_WIDTH - 1);
            const double g = double(j) / (IMAGE_HEIGHT - 1);
            const double b = 0.5;

            const uint8_t ir = static_cast<uint8_t>(255.0 * r);
            const uint8_t ig = static_cast<uint8_t>(255.0 * g);
            const uint8_t ib = static_cast<uint8_t>(255.0 * b);

            pixels[j * IMAGE_WIDTH + i] = { ir, ig, ib };
        }
    }

    WritePPM("RayTracedImage.ppm", IMAGE_WIDTH, IMAGE_HEIGHT, pixels);

    return EXIT_SUCCESS;
}
