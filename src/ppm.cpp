#include <fstream>
#include "ppm.hpp"

namespace RT
{
    bool WritePPM(const char* filename, unsigned int width, unsigned int height, const uint8_t* pixels)
    {
        // Bytes per pixels
        constexpr unsigned int bpp = 3;

        std::ofstream ppmFile{filename, std::ios::binary};

        if (!ppmFile.is_open()) {
            return false;
        }

        ppmFile << "P3\n" << width << " " << height << "\n255\n";

        for (unsigned int j = 0; j < height; ++j) {
            for (unsigned int i = 0; i < width * bpp; i += bpp) {
                const unsigned int index = j * width * bpp + i;

                const unsigned int& r = static_cast<unsigned int>(pixels[index + 0]);
                const unsigned int& g = static_cast<unsigned int>(pixels[index + 1]);
                const unsigned int& b = static_cast<unsigned int>(pixels[index + 2]);

                ppmFile << r << " " << g << " " << b << "\n";
            }
        }

        return true;
    }
}
