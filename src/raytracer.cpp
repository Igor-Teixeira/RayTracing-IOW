#include <cstdint>
#include <iostream>
#include <vector>
#include "ppm.hpp"

namespace RT
{
    bool RayTrace(unsigned int imageWidth, unsigned int imageHeight, const char* filename)
    {
        struct RGB
        {
            uint8_t r;
            uint8_t g;
            uint8_t b;
        };

        std::vector<RGB> pixels(imageWidth * imageHeight);

        for (unsigned int j = 0; j < imageHeight; ++j) {
            std::cout << "\rScanlines remaining: " << imageHeight - 1 - j << " " << std::flush;

            for (unsigned int i = 0; i < imageWidth; ++i) {
                const float r = float(i) / (imageWidth - 1);
                const float g = float(j) / (imageHeight - 1);
                const float b = 0.5f;

                RGB& pixel = pixels[j * imageWidth + i];

                pixel.r = static_cast<uint8_t>(255.0f * r);
                pixel.g = static_cast<uint8_t>(255.0f * g);
                pixel.b = static_cast<uint8_t>(255.0f * b);
            }
        }

        std::cout << "\rWriting PPM file...          " << std::flush;

        if (!RT::WritePPM(filename, imageWidth, imageHeight, reinterpret_cast<const uint8_t*>(pixels.data()))) {
            std::cerr << "Failed to write PPM file: " << filename << std::endl;
            return false;
        }

        std::cout << "\rDone!                      \n" << std::flush;

        return true;
    }
}
