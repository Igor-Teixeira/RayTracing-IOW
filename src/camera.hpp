#pragma once
#include "hittable.hpp"
#include "rtmath.hpp"

namespace RT
{
    class Camera
    {
    public:
        Camera(unsigned int imageWidth, unsigned int imageHeight, const Point3& position);
        bool Render(const char* filename, const Hittable& world);
    
    private:
        Color TraceRay(const Ray& ray, const Hittable& world);

    private:
        unsigned int m_ImageWidth;
        unsigned int m_ImageHeight;

        Point3 m_Position;

        Point3 m_Pixel00Location;
        Vec3 m_PixelDeltaU;
        Vec3 m_PixelDeltaV;
    };
}
