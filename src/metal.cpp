#include "rtmath.hpp"
#include "material.hpp"
#include "hittable.hpp"
#include "metal.hpp"

namespace RT
{
    bool Metal::Scatter(const Ray& incident, const HitInfo& hitInfo, Color* attenuation, Ray* scattered)
    {
        const Vec3 reflected = Reflect(Normalize(incident.direction()), hitInfo.normal);
        const Vec3 scatterDirection = reflected + m_Fuzz * Normalize(RandomVec3InUnitSphere());

        *scattered = Ray{hitInfo.point, scatterDirection};
        *attenuation = m_Albedo;

        return (Dot(scatterDirection, hitInfo.normal) > 0.0f);
    }
}
