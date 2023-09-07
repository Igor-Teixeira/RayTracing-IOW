#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <vector>
#include "ppm.hpp"
#include "rtmath.hpp"

int main()
{
    constexpr unsigned int IMAGE_WIDTH = 256;
    constexpr unsigned int IMAGE_HEIGHT = 256;
    const char* filename = "RayTracing.ppm";

    struct RGB
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    std::vector<RGB> pixels(IMAGE_WIDTH * IMAGE_HEIGHT);

    for (unsigned int j = 0; j < IMAGE_HEIGHT; ++j) {
        std::cout << "\rScanlines remaining: " << IMAGE_HEIGHT - 1 - j << " " << std::flush;

        for (unsigned int i = 0; i < IMAGE_WIDTH; ++i) {
            const float r = float(i) / (IMAGE_WIDTH - 1);
            const float g = float(j) / (IMAGE_HEIGHT - 1);
            const float b = 0.5f;

            RGB& pixel = pixels[j * IMAGE_WIDTH + i];

            pixel.r = static_cast<uint8_t>(255.0f * r);
            pixel.g = static_cast<uint8_t>(255.0f * g);
            pixel.b = static_cast<uint8_t>(255.0f * b);
        }
    }

    std::cout << "\rWriting PPM file...          " << std::flush;

    if (!RT::WritePPM(filename, IMAGE_WIDTH, IMAGE_HEIGHT, reinterpret_cast<const uint8_t*>(pixels.data()))) {
        std::cerr << "Failed to write PPM file: " << filename << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "\rDone!                      \n" << std::flush;
    return EXIT_SUCCESS;
}
