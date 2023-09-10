#pragma once
#include "material.hpp"

namespace RT
{
    class Dielectric : public Material
    {
    public:
        Dielectric(float refractiveIndex)
            : m_RefractiveIndex(refractiveIndex)
        {
        }

        virtual bool Scatter(const Ray& incident, const HitInfo& hitInfo, Color* attenuation, Ray* scattered) override;

    private:
        float m_RefractiveIndex;
    };
}
