#include <cstdlib>
#include <iostream>
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"

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

    RT::HittableList world;
    world.Add<RT::Sphere>(RT::Point3{0.0f, 0.0f, -1.0f}, 0.5f);
    world.Add<RT::Sphere>(RT::Point3{0.0f, -100.5f, -1.0f}, 100.0f);

    RT::Camera camera{imageWidth, imageHeight, RT::Point3{0.0f}};

    if (!camera.Render(filename, world)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
