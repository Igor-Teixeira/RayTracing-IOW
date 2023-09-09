#pragma once
#include "rtmath.hpp"

namespace RT
{
    class Material;

    struct HitInfo
    {
        Point3 point;
        Vec3 normal;
        float t;
        bool frontFace;
        Material* material;

        void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal)
        {
            frontFace = Dot(ray.direction(), outwardNormal) < 0.0f;
            normal = frontFace ? outwardNormal : -outwardNormal;
        }
    };

    class Hittable
    {
    public:
        virtual ~Hittable() = default;

        virtual bool Hit(const Ray& ray, const Interval& rayInterval, HitInfo* hitInfo) const = 0;
    };
}
