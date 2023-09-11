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
    std::cout << "Usage: Raytracer [width (px)] [height (px)] [samples] [output file]" << std::endl;
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

    if (argc != 5) {
        PrintUsage();
        return EXIT_FAILURE;
    }

    const unsigned int imageWidth = GetUIntArg(argv[1]);
    const unsigned int imageHeight = GetUIntArg(argv[2]);
    const unsigned int samples = GetUIntArg(argv[3]);
    const char* const filename = argv[4];

    if (imageWidth == 0 || imageHeight == 0 || samples == 0) {
        PrintUsage();
        return EXIT_FAILURE;
    }

    std::cout << "Raytracing [" << imageWidth << "x" << imageHeight << "] " << samples << " samples image to file: " << filename << std::endl;

    HittableList world;

    world.Add<Sphere>(Point3{0.0f, -1000.0f, 0.0f}, 1000.0f, std::make_unique<Lambertian>(Color{0.5f, 0.5f, 0.5f}));

    for (int a = -11; a < 11; ++a) {
        for (int b = -11; b < 11; ++b) {
            const float randomMaterial = RandomFloat();
            const Point3 center = Point3{a + 0.9f * RandomFloat(), 0.2f, b + 0.9f * RandomFloat()};

            if (Length(center - Point3{4.0f, 0.2f, 0.0f}) > 0.9f) {
                if (randomMaterial < 0.5f) {
                    const Color albedo = Hadamard(RandomVec3(), RandomVec3());
                    world.Add<Sphere>(center, 0.2f, std::make_unique<Lambertian>(albedo));
                }
                else if (randomMaterial < 0.90f) {
                    const Color albedo = RandomVec3(0.5f, 1.0f);
                    const float fuzz = RandomFloat(0.0f, 0.5f);
                    world.Add<Sphere>(center, 0.2f, std::make_unique<Metal>(albedo, fuzz));
                }
                else {
                    world.Add<Sphere>(center, 0.2f, std::make_unique<Dielectric>(1.5f));
                }
            }
        }
    }

    world.Add<Sphere>(Point3{0.0f, 1.0f, 0.0f}, 1.0f, std::make_unique<Dielectric>(1.5f));
    world.Add<Sphere>(Point3{-4.0f, 1.0f, 0.0f}, 1.0f, std::make_unique<Lambertian>(Color{0.4f, 0.2f, 0.1f}));
    world.Add<Sphere>(Point3{4.0f, 1.0f, 0.0f}, 1.0f, std::make_unique<Metal>(Color{0.7f, 0.6f, 0.5f}, 0.0f));

    CameraSettings cameraSettings;
    cameraSettings.imageWidth = imageWidth;
    cameraSettings.imageHeight = imageHeight;

    cameraSettings.samples = static_cast<int>(samples);
    cameraSettings.maxTracingDepth = 50;

    cameraSettings.position = Vec3{13.0f, 2.0f, 3.0f};
    cameraSettings.lookAt = Vec3{0.0f, 0.0f, 0.0f};
    cameraSettings.verticalFOV = 20.0f;

    cameraSettings.defocusAngle = 0.6f;
    cameraSettings.focalDistance = 10.0f;

    Camera camera{cameraSettings};

    if (!camera.Render(filename, world)) {
        return EXIT_FAILURE;
    }

    // In minutes
    const double timeTaken = executionTimer.Peek();

    std::cout << "Time taken: ";

    if (timeTaken < 1.0) {
        std::cout << (timeTaken * 60.0) << " sec" << std::endl;
    }
    else if (timeTaken > 60.0) {
        std::cout << (timeTaken / 60.0) << " hrs" << std::endl;
    }
    else {
        std::cout << timeTaken << " min" << std::endl;
    }

    return EXIT_SUCCESS;
}
