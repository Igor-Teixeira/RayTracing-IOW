#include "rtmath.hpp"
#include "hittable.hpp"
#include "dielectric.hpp"

namespace RT
{
    static float Reflectance(float cosine, float refractionRatio)
    {
        float r0 = (1.0f - refractionRatio) / (1.0f + refractionRatio);
        r0 = r0 * r0;

        return r0 + (1.0f - r0) * std::pow((1.0f - cosine), 5.0f);
    }

    bool Dielectric::Scatter(const Ray& incident, const HitInfo& hitInfo, Color* attenuation, Ray* scattered)
    {
        *attenuation = Color{1.0f, 1.0f, 1.0f};

        const float refractionRatio = hitInfo.frontFace ? (1.0f / m_RefractiveIndex) : m_RefractiveIndex;

        const Vec3 unitIncident = Normalize(incident.direction());

        const float cosTheta = std::min(Dot(-unitIncident, hitInfo.normal), 1.0f);
        const float sinTheta = std::sqrt(1.0f - cosTheta * cosTheta);

        Vec3 scatterDirection;
        const bool cannotRefract = (refractionRatio * sinTheta) > 1.0f;

        if (cannotRefract || (Reflectance(cosTheta, refractionRatio) > RandomFloat())) {
            scatterDirection = Reflect(unitIncident, hitInfo.normal);
        }
        else {
            scatterDirection = Refract(unitIncident, hitInfo.normal, refractionRatio);
        }

        *scattered = Ray{hitInfo.point, scatterDirection};
        return true;
    }
}
