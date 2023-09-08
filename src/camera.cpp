#include <iostream>
#include <vector>
#include "ppm.hpp"
#include "hittable.hpp"
#include "camera.hpp"

namespace RT
{
    Camera::Camera(unsigned int imageWidth, unsigned int imageHeight, const Point3& position)
        : m_ImageWidth(imageWidth), m_ImageHeight(imageHeight), m_Position(position)
    {
        const float focalLength = 1.0f;
        const float viewportHeight = 2.0f;
        const float viewportWidth = viewportHeight * (static_cast<float>(imageWidth) / imageHeight);

        const Vec3 viewportU{viewportWidth, 0.0f, 0.0f};
        const Vec3 viewportV{0.0f, -viewportHeight, 0.0f};

        m_PixelDeltaU = viewportU / static_cast<float>(imageWidth);
        m_PixelDeltaV = viewportV / static_cast<float>(imageHeight);

        const Vec3 viewportUpperLeft =
            m_Position - Vec3(0.0f, 0.0f, focalLength) - (viewportU * 0.5f) - (viewportV * 0.5f);

        m_Pixel00Location = viewportUpperLeft + (m_PixelDeltaU + m_PixelDeltaV) * 0.5f;
    }

    bool Camera::Render(const char* filename, const Hittable& world)
    {
        std::vector<Color> pixels(m_ImageWidth * m_ImageHeight);

        for (unsigned int j = 0; j < m_ImageHeight; ++j) {
            std::cout << "\rScanlines remaining: " << m_ImageHeight - j << " " << std::flush;

            for (unsigned int i = 0; i < m_ImageWidth; ++i) {
                const Vec3 pixelCenter = m_Pixel00Location + (static_cast<float>(i) * m_PixelDeltaU) + (static_cast<float>(j) * m_PixelDeltaV);
                const Vec3 rayDirection = pixelCenter - m_Position;

                const Ray ray{m_Position, rayDirection};

                const Color pixelColor = TraceRay(ray, world);

                pixels[j * m_ImageWidth + i] = pixelColor;
            }
        }

        std::cout << "\rWriting PPM file...          " << std::flush;

        if (!WritePPM(filename, m_ImageWidth, m_ImageHeight, reinterpret_cast<const float*>(pixels.data()))) {
            std::cerr << "Failed to write PPM file: " << filename << std::endl;
            return false;
        }

        std::cout << "\rDone!                      \n" << std::flush;

        return true;
    }

    Color Camera::TraceRay(const Ray& ray, const Hittable& world)
    {
        HitInfo hitInfo;
        if (world.Hit(ray, Interval{0.0f, FltInfinity}, &hitInfo)) {
            return 0.5f * (hitInfo.normal + Vec3{1.0f});
        }

        const Vec3 unitRayDirection = Normalize(ray.direction());
        const float a = 0.5f * (unitRayDirection.y + 1.0f);

        return Lerp(Vec3{1.0f}, Vec3{0.0f, 0.0f, 1.0f}, a);
    }
}
