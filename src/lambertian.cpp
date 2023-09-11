#include "rtmath.hpp"
#include "material.hpp"
#include "hittable.hpp"
#include "lambertian.hpp"

namespace RT
{
    bool Lambertian::Scatter(const Ray& incident, const HitInfo& hitInfo, Color* attenuation, Ray* scattered)
    {
        (void)incident;

        Vec3 scatterDirection = hitInfo.normal + Normalize(RandomVec3InUnitSphere());

        while (NearZero(scatterDirection)) {
            scatterDirection = hitInfo.normal + Normalize(RandomVec3InUnitSphere());
        }

        *scattered = Ray{hitInfo.point, scatterDirection};
        *attenuation = m_Albedo;
        return true;
    }
}
