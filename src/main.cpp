#include <cstdlib>
#include <iostream>
#include "timer.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
#include "dielectric.hpp"
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
    using namespace RT;

    Timer executionTimer{};

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

    HittableList world;
    // Ground sphere
    world.Add<Sphere>(Point3{0.0f, -100.501f, 0.0f}, 100.0f, std::make_unique<Lambertian>(Color{0.5f, 0.5f, 0.5f}));
    // Center sphere
    world.Add<Sphere>(Point3{0.0f, 0.0f, 0.0f}, 0.5f, std::make_unique<Dielectric>(1.5f));
    // Left sphere
    world.Add<Sphere>(Point3{-1.05f, 0.0f, 0.0f}, 0.5f, std::make_unique<Metal>(Color{0.3f, 0.3f, 0.7f}, 0.0f));
    // Right sphere
    world.Add<Sphere>(Point3{1.05f, 0.0f, 0.0f}, 0.5f, std::make_unique<Lambertian>(Color{0.8f, 0.6f, 0.2f}));

    CameraSettings cameraSettings;
    cameraSettings.imageWidth = imageWidth;
    cameraSettings.imageHeight = imageHeight;
    cameraSettings.samples = 100;
    cameraSettings.maxTracingDepth = 50;
    cameraSettings.position = Vec3{0.0f, 0.0f, 1.3f};
    cameraSettings.lookAt = Vec3{0.0f, 0.0f, 0.0f};
    cameraSettings.verticalFOV = 90.0f;

    Camera camera{cameraSettings};

    if (!camera.Render(filename, world)) {
        return EXIT_FAILURE;
    }

    const double timeTaken = executionTimer.Peek();

    if (timeTaken < 1.0) {
        std::cout << "Time taken: " << (timeTaken * 60.0) << " sec" << std::endl;
    }
    else {
        std::cout << "Time taken: " << timeTaken << " min" << std::endl;
    }

    return EXIT_SUCCESS;
}
