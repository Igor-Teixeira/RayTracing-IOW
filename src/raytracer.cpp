#include <cstdint>
#include <iostream>
#include <vector>
#include <limits>
#include "ppm.hpp"
#include "rtmath.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

namespace RT
{
    Color TraceRay(const Ray& ray, const Hittable& world)
    {
        HitInfo hitInfo;
        if (world.Hit(ray, Interval{0.0f, FltInfinity}, &hitInfo)) {
            return 0.5f * (hitInfo.normal + Vec3{1.0f});
        }

        const Vec3 unitRayDirection = Normalize(ray.direction());
        const float a = 0.5f * (unitRayDirection.y + 1.0f);

        return Lerp(Vec3{1.0f}, Vec3{0.0f, 0.0f, 1.0f}, a);
    }

    bool RayTrace(unsigned int imageWidth, unsigned int imageHeight, const char* filename)
    {
        const float focalLength = 1.0f;
        const float viewportHeight = 2.0f;
        const float viewportWidth = viewportHeight * (static_cast<float>(imageWidth) / imageHeight);

        const Point3 cameraCenter{0.0f};

        const Vec3 viewportU{viewportWidth, 0.0f, 0.0f};
        const Vec3 viewportV{0.0f, -viewportHeight, 0.0f};

        const Vec3 pixelDeltaU = viewportU / static_cast<float>(imageWidth);
        const Vec3 pixelDeltaV = viewportV / static_cast<float>(imageHeight);

        const Vec3 viewportUpperLeft =
            cameraCenter - Vec3(0.0f, 0.0f, focalLength) - (viewportU * 0.5f) - (viewportV * 0.5f);

        const Vec3 pixel00Location = viewportUpperLeft + (pixelDeltaU + pixelDeltaV) * 0.5f;

        HittableList world;
        world.Add<Sphere>(Point3{0.0f, 0.0f, -1.0f}, 0.5f);
        world.Add<Sphere>(Point3{0.0f, -100.5f, -1.0f}, 100.0f);

        std::vector<Color> pixels(imageWidth * imageHeight);

        for (unsigned int j = 0; j < imageHeight; ++j) {
            std::cout << "\rScanlines remaining: " << imageHeight - j << " " << std::flush;

            for (unsigned int i = 0; i < imageWidth; ++i) {
                const Vec3 pixelCenter = pixel00Location + (static_cast<float>(i) * pixelDeltaU) + (static_cast<float>(j) * pixelDeltaV);
                const Vec3 rayDirection = pixelCenter - cameraCenter;

                const Ray ray{cameraCenter, rayDirection};

                const Color pixelColor = TraceRay(ray, world);

                pixels[j * imageWidth + i] = pixelColor;
            }
        }

        std::cout << "\rWriting PPM file...          " << std::flush;

        if (!RT::WritePPM(filename, imageWidth, imageHeight, reinterpret_cast<const float*>(pixels.data()))) {
            std::cerr << "Failed to write PPM file: " << filename << std::endl;
            return false;
        }

        std::cout << "\rDone!                      \n" << std::flush;

        return true;
    }
}
