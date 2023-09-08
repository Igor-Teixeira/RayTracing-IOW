#include <cstdint>
#include <iostream>
#include <vector>
#include "ppm.hpp"
#include "rtmath.hpp"

namespace RT
{
    float HitSphere(const Point3& center, float radius, const Ray& ray)
    {
        const Vec3& oc = ray.origin() - center;

        const float a = Dot(ray.direction(), ray.direction());
        const float b = 2.0f * Dot(oc, ray.direction());
        const float c = Dot(oc, oc) - radius * radius;

        const float discriminant = b * b - 4.0f * a * c;

        if (discriminant < 0.0f) {
            return -1.0f;
        }
        else {
            return (-b - std::sqrt(discriminant)) / (2.0f * a);
        }
    }

    Color TraceRay(const Ray& ray)
    {
        const float t = HitSphere(Vec3{0.0f, 0.0f, -1.0f}, 0.5f, ray);

        if (t > 0.0f) {
            const Vec3 normal = Normalize(ray.at(t) - Vec3{0.0f, 0.0f, -1.0f});
            return 0.5f * Color{normal + Vec3{1.0f}};
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

        std::vector<Color> pixels(imageWidth * imageHeight);

        for (unsigned int j = 0; j < imageHeight; ++j) {
            std::cout << "\rScanlines remaining: " << imageHeight - j << " " << std::flush;

            for (unsigned int i = 0; i < imageWidth; ++i) {
                const Vec3 pixelCenter = pixel00Location + (static_cast<float>(i) * pixelDeltaU) + (static_cast<float>(j) * pixelDeltaV);
                const Vec3 rayDirection = pixelCenter - cameraCenter;

                const Ray ray{cameraCenter, rayDirection};

                const Color pixelColor = TraceRay(ray);

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
