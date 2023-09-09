#pragma once
#include "rtmath.hpp"
#include "material.hpp"

namespace RT
{
    class Lambertian : public Material
    {
    public:
        Lambertian(const Color& albedo)
            : m_Albedo(albedo)
        {
        }

        virtual bool Scatter(const Ray& incident, const HitInfo& hitInfo, Color* attenuation, Ray* scattered) override;

    private:
        Color m_Albedo;
    };
}
