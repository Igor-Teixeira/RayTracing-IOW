#pragma once
#include <cmath>

namespace RT
{
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

    inline const Vec3 operator+(Vec3 lhs, const Vec3& rhs) { lhs += rhs; return lhs; }
    inline const Vec3 operator-(Vec3 lhs, const Vec3& rhs) { lhs -= rhs; return lhs; }
    inline const Vec3 operator*(Vec3 lhs, float rhs) { lhs *= rhs; return lhs; }
    inline const Vec3 operator/(Vec3 lhs, float rhs) { lhs /= rhs; return lhs; }
    inline const Vec3 operator*(float lhs, Vec3 rhs) { rhs *= lhs; return rhs; }
    inline const Vec3 operator/(float lhs, Vec3 rhs) { rhs /= lhs; return rhs; }

    inline const float LengthSquared(const Vec3& v)
    {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }

    inline const float Length(const Vec3& v)
    {
        return std::sqrt(LengthSquared(v));
    }

    inline const Vec3 Normalize(const Vec3& v)
    {
        return v / Length(v);
    }

    using Point3 = Vec3;

    class Ray
    {
    public:
        Ray() = default;

        Ray(const Point3& origin, const Vec3& direction)
            : m_Origin(origin), m_Direction(direction)
        {
        }

        const Point3& origin() const { return m_Origin; }
        const Vec3& direction() const { return m_Direction; }

        const Point3& at(float t) const { return t * m_Direction + m_Origin; }

    private:
        const Point3 m_Origin;
        const Vec3 m_Direction;
    };
}