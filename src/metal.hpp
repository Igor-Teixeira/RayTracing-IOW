#pragma once
#include "rtmath.hpp"
#include "material.hpp"

namespace RT
{
    class Metal : public Material
    {
    public:
        Metal(const Color& albedo, float fuzz)
            : m_Albedo(albedo), m_Fuzz(fuzz < 1.0f ? fuzz : 1.0f)
        {
        }

        virtual bool Scatter(const Ray& incident, const HitInfo& hitInfo, Color* attenuation, Ray* scattered) override;

    private:
        Color m_Albedo;
        float m_Fuzz;
    };
}
