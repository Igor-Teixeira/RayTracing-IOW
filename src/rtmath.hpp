#pragma once
#include <cmath>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <numbers>

namespace RT
{
    inline auto FltInfinity = std::numeric_limits<float>::infinity();

    struct Vec3
    {
        float x;
        float y;
        float z;

        Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
        Vec3(float scalar) : x(scalar), y(scalar), z(scalar) {}
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

        float* data() { return reinterpret_cast<float*>(this); }
        const float* data() const { return reinterpret_cast<const float*>(this); }

        float& operator[](int index) { return reinterpret_cast<float*>(this)[index]; }
        const float& operator[](int index) const { return reinterpret_cast<const float*>(this)[index]; }

        const Vec3 operator-() const { return Vec3(-this->x, -this->y, -this->z); }

        Vec3& operator+=(const Vec3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
        Vec3& operator-=(const Vec3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
        Vec3& operator*=(float rhs) { x *= rhs; y *= rhs; z *= rhs; return *this; }
        Vec3& operator/=(float rhs) { const float inv = 1.0f / rhs; x *= inv; y *= inv; z *= inv; return *this; }
    };

    using Point3 = Vec3;
    using Color = Vec3;

    inline const Vec3 operator+(Vec3 lhs, const Vec3& rhs) { lhs += rhs; return lhs; }
    inline const Vec3 operator-(Vec3 lhs, const Vec3& rhs) { lhs -= rhs; return lhs; }
    inline const Vec3 operator*(Vec3 lhs, float rhs) { lhs *= rhs; return lhs; }
    inline const Vec3 operator/(Vec3 lhs, float rhs) { lhs /= rhs; return lhs; }
    inline const Vec3 operator*(float lhs, Vec3 rhs) { rhs *= lhs; return rhs; }
    inline const Vec3 operator/(float lhs, Vec3 rhs) { rhs /= lhs; return rhs; }

    inline float ToRadians(float degrees)
    {
        constexpr float factor = std::numbers::pi_v<float> / 180.0f;
        return degrees * factor;
    }

    inline float LengthSquared(const Vec3& v)
    {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }

    inline float Length(const Vec3& v)
    {
        return std::sqrt(LengthSquared(v));
    }

    inline const Vec3 Normalize(const Vec3& v)
    {
        return v / Length(v);
    }

    inline const Vec3 Lerp(const Vec3& a, const Vec3& b, float t)
    {
        return (1.0f - t) * a + t * b;
    }

    inline float Dot(const Vec3& a, const Vec3& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    inline const Vec3 Cross(const Vec3& a, const Vec3& b)
    {
        return Vec3{a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
    }

    inline const Vec3 Hadamard(const Vec3& a, const Vec3& b)
    {
        return Vec3{a.x * b.x, a.y * b.y, a.z * b.z};
    }

    inline bool NearZero(const Vec3& v)
    {
        constexpr float s = 1.0E-5f;
        return (std::fabs(v.x) < s) && (std::fabs(v.y) < s) && (std::fabs(v.z) < s);
    }

    inline const Vec3 Reflect(const Vec3& v, const Vec3& n)
    {
        return v - 2.0f * Dot(v, n) * n;
    }

    inline const Vec3 Refract(const Vec3& incident, const Vec3& normal, float refractionRatio)
    {
        const float cosTheta = std::min(Dot(-incident, normal), 1.0f);
        const Vec3 outPerpendicular = refractionRatio * (incident + cosTheta * normal);
        const Vec3 outParallel = -std::sqrt(std::fabs(1.0f - LengthSquared(outPerpendicular))) * normal;

        return outPerpendicular + outParallel;
    }

    class Ray
    {
    public:
        Ray() = default;
        Ray(const Point3& origin, const Vec3& direction) : m_Origin(origin), m_Direction(direction) {}

        const Point3& origin() const { return m_Origin; }
        const Vec3& direction() const { return m_Direction; }

        const Point3 at(float t) const { return t * m_Direction + m_Origin; }

    private:
        Point3 m_Origin;
        Vec3 m_Direction;
    };

    class Interval
    {
    public:
        Interval() : m_Min(FltInfinity), m_Max(-FltInfinity) {}
        Interval(float min, float max) : m_Min(min), m_Max(max) {}

        float Min() const { return m_Min; }
        float Max() const { return m_Max; }

        bool Contains(float x) const { return x >= m_Min && x <= m_Max; }
        bool Surrounds(float x) const { return x > m_Min && x < m_Max; }

        float Clamp(float x)
        {
            if (x < m_Min) { return m_Min; };
            if (x > m_Max) { return m_Max; };

            return x;
        }

        static Interval Empty() { return Interval(FltInfinity, -FltInfinity); }
        static Interval Universe() { return Interval(-FltInfinity, FltInfinity); }

    private:
        float m_Min;
        float m_Max;
    };

    float RandomFloat();
    float RandomFloat(float min, float max);
    const Vec3 RandomVec3();
    const Vec3 RandomVec3(float min, float max);

    const Vec3 RandomVec3InUnitSphere();
    const Vec3 RandomVec3InHemisphere(const Vec3& normal);
}
