#pragma once
#include "hittable.hpp"
#include "rtmath.hpp"

namespace RT
{
    struct CameraSettings
    {
        unsigned int imageWidth;
        unsigned int imageHeight;
        unsigned int samples;
        int maxTracingDepth;

        Point3 position;
        Point3 lookAt;
        float verticalFOV;
    };

    class Camera
    {
    public:
        Camera(const CameraSettings& settings);
        bool Render(const char* filename, const Hittable& world);
    
    private:
        Color TraceRay(const Ray& ray, int depth, const Hittable& world);
        Ray GetRay(unsigned int i, unsigned int j);

        float LinearToGamma(float linear);

        const Vec3 PixelSampleSquare();

    private:
        unsigned int m_ImageWidth;
        unsigned int m_ImageHeight;
        unsigned int m_SamplesPerPixel;
        int m_MaxDepth;

        Point3 m_Position;
        Point3 m_LookAt;
        float m_VerticalFOV;

        Point3 m_Pixel00Location;
        Vec3 m_PixelDeltaU;
        Vec3 m_PixelDeltaV;
    };
}
