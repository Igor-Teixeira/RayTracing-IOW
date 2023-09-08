#pragma once
#include <memory>
#include <vector>
#include <utility>
#include "hittable.hpp"

namespace RT
{
    class HittableList : public Hittable
    {
    public:
        HittableList() = default;

        template<typename T, typename... Args>
        void Add(Args&&... args)
        {
            auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
            m_Objects.emplace_back(std::move(ptr));
        }

        virtual bool Hit(const Ray& ray, const Interval& rayInterval, HitInfo* hitInfo) const override
        {
            bool anyHits = false;
            float closestHit = rayInterval.Max();

            HitInfo info;

            for (auto& object : m_Objects) {
                if (object->Hit(ray, Interval{rayInterval.Min(), closestHit}, &info)) {
                    anyHits = true;
                    closestHit = info.t;
                    *hitInfo = info;
                }
            }

            return anyHits;
        }

    private:
        std::vector<std::unique_ptr<Hittable>> m_Objects;
    };
}
