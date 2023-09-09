#include "rtmath.hpp"
#include "material.hpp"
#include "hittable.hpp"
#include "lambertian.hpp"

namespace RT
{
    bool Lambertian::Scatter(const Ray& incident, const HitInfo& hitInfo, Color* attenuation, Ray* scattered)
    {
        Vec3 scatterDirection = hitInfo.normal + RandomVec3InUnitSphere();

        while (NearZero(scatterDirection)) {
            scatterDirection = hitInfo.normal + RandomVec3InUnitSphere();
        }

        *scattered = Ray{hitInfo.point, scatterDirection};
        *attenuation = m_Albedo;
        return true;
    }
}
