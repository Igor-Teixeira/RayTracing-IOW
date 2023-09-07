#include <cstdlib>
#include <iostream>
#include "raytracer.hpp"

static void PrintUsage()
{
    std::cout << "Invalid parameters!\n";
    std::cout << "Usage: Raytracer [width (px)] [height (px)] [output file]" << std::endl;
}

static unsigned int GetUIntArg(const char* const arg)
{
    const int r = std::atoi(arg);
    return (r <= 0 ? 0 : r);
}

int main(int argc, char* argv[])
{
    if (argc != 4) {
        PrintUsage();
        return EXIT_FAILURE;
    }

    const unsigned int imageWidth = GetUIntArg(argv[1]);
    const unsigned int imageHeight = GetUIntArg(argv[2]);
    const char* const filename = argv[3];

    if (imageWidth == 0 || imageHeight == 0) {
        PrintUsage();
        return EXIT_FAILURE;
    }

    std::cout << "Raytracing [" << imageWidth << "x" << imageHeight << "] image to file: " << filename << std::endl;

    if (!RT::RayTrace(imageWidth, imageHeight, filename)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
