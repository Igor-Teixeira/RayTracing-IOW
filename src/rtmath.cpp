#include <random>
#include "rtmath.hpp"

namespace RT
{
    static std::random_device s_RD{};
    static std::seed_seq seed{s_RD(), s_RD(), s_RD(), s_RD(), s_RD(), s_RD(), s_RD(), s_RD()};

    static std::mt19937 s_RNG{seed};
    static std::uniform_real_distribution<float> s_Dist{0.0f, 1.0f};

    float RandomFloat()
    {
        return s_Dist(s_RNG);
    }

    float RandomFloat(float min, float max)
    {
        return min + (max - min) * RandomFloat();
    }

    const Vec3 RandomVec3()
    {
        return Vec3{RandomFloat(), RandomFloat(), RandomFloat()};
    }

    const Vec3 RandomVec3(float min, float max)
    {
        return Vec3{RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max)};
    }

    const Vec3 RandomVec3InUnitSphere()
    {
        while (true) {
            const Vec3 v = RandomVec3(-1.0f, 1.0f);

            if (LengthSquared(v) < 1.0f) {
                return v;
            }
        }
    }

    const Vec3 RandomVec3InHemisphere(const Vec3& normal)
    {
        const Vec3& direction = RandomVec3InUnitSphere();

        if (Dot(direction, normal) > 0.0f) {
            return direction;
        }
        else {
            return -direction;
        }
    }

    const Vec3 RandomVec3InUnitDisk()
    {
        while (true) {
            const Vec3 v = Vec3{RandomFloat(-1.0f, 1.0f), RandomFloat(-1.0f, 1.0f), 0.0f};
            if (LengthSquared(v) < 1.0f) {
                return v;
            }
        }
    }
}
