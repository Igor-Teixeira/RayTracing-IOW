#pragma once
#include <memory>
#include "hittable.hpp"
#include "material.hpp"

namespace RT
{
    class Sphere : public Hittable
    {
    public:
        Sphere(const Point3& center, float radius, std::unique_ptr<Material> material)
            : m_Center(center), m_Radius(radius), m_Material(std::move(material))
        {
        }

        virtual bool Hit(const Ray& ray, const Interval& rayInterval, HitInfo* hitInfo) const override
        {
            const Vec3 oc = ray.origin() - m_Center;
            const float a = LengthSquared(ray.direction());
            const float half_b = Dot(oc, ray.direction());
            const float c = LengthSquared(oc) - m_Radius * m_Radius;

            const float discriminant = half_b * half_b - a * c;

            if (discriminant < 0.0f) {
                return false;
            }

            const float sqrtDisc = std::sqrt(discriminant);

            float root = (-half_b - sqrtDisc) / a;

            if (!rayInterval.Surrounds(root)) {
                root = (-half_b + sqrtDisc) / a;

                if (!rayInterval.Surrounds(root)) {
                    return false;
                }
            }

            hitInfo->t = root;
            hitInfo->point = ray.at(hitInfo->t);
            const Vec3 outwardNormal = (hitInfo->point - m_Center) / m_Radius;
            hitInfo->SetFaceNormal(ray, outwardNormal);
            hitInfo->material = m_Material.get();

            return true;
        }

    private:
        Point3 m_Center;
        float m_Radius;
        std::unique_ptr<Material> m_Material;
    };
}
