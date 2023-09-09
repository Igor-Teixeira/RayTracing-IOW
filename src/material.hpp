#pragma once
#include "rtmath.hpp"

namespace RT
{
    struct HitInfo;

    class Material
    {
    public:
        virtual ~Material() = default;

        virtual bool Scatter(const Ray& incident, const HitInfo& hitInfo, Color* attenuation, Ray* scattered) = 0;
    };
}
