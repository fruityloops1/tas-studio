#pragma once

#include <cmath>
#include <cstdint>
#include <string>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef float f32;
typedef double f64;

namespace fl {

template <class T>
struct Vector2 {
    T x, y;

    inline bool operator==(const Vector2& a) const
    {
        return x == a.x && y == a.y;
    }
    inline Vector2 operator+(const Vector2& a) const
    {
        return { x + a.x, y + a.x };
    }
    inline Vector2 operator-(const Vector2& a) const
    {
        return { x - a.x, y - a.x };
    }
    inline Vector2 operator*(const Vector2& a) const
    {
        return { x * a.x, y * a.y };
    }
    inline Vector2 operator/(const Vector2& a) const
    {
        return { x / a.x, y / a.y };
    }
    inline Vector2 operator+(float f) const
    {
        return { x + f, y + f };
    }
    inline Vector2 operator-(float f) const
    {
        return { x - f, y - f };
    }
    inline Vector2 operator*(float f) const
    {
        return { x * f, y * f };
    }
    inline Vector2 operator/(float f) const
    {
        return { x / f, y / f };
    }
    inline void operator+=(const Vector2& a)
    {
        x += a.x;
        y += a.y;
    }
    inline void operator-=(const Vector2& a)
    {
        x -= a.x;
        y -= a.y;
    }
    inline void operator*=(const Vector2& a)
    {
        x *= a.x;
        y *= a.y;
    }
    inline void operator/=(const Vector2& a)
    {
        x /= a.x;
        y /= a.y;
    }
    inline void operator+=(float a)
    {
        x += a;
        y += a;
    }
    inline void operator-=(float a)
    {
        x -= a;
        y -= a;
    }
    inline void operator*=(float a)
    {
        x *= a;
        y *= a;
    }
    inline void operator/=(float a)
    {
        x /= a;
        y /= a;
    }

    inline T squaredLength()
    {
        return x * x + y * y;
    }
    inline T length() { return std::sqrt(squaredLength()); }
    inline Vector2 normalize()
    {
        Vector2 normalized = *this;
        const T len = normalized.length();
        if (len > 0) {
            const T inv_len = 1 / len;
            normalized.x *= inv_len;
            normalized.y *= inv_len;
        }
        return normalized;
    }

    std::string toString()
    {
        std::string val = std::to_string(x);
        val.append(" ");
        val.append(std::to_string(y));
        return val;
    }
};

template <class T>
struct Vector3 {
    T x, y, z;

    inline bool operator==(const Vector3& a) const
    {
        return x == a.x && y == a.y && z == a.z;
    }
    inline Vector3 operator+(const Vector3& a) const
    {
        return { x + a.x, y + a.y, z + a.z };
    }
    inline Vector3 operator-(const Vector3& a) const
    {
        return { x - a.x, y - a.y, z - a.z };
    }
    inline Vector3 operator*(const Vector3& a) const
    {
        return { x * a.x, y * a.y, z * a.z };
    }
    inline Vector3 operator/(const Vector3& a) const
    {
        return { x / a.x, y / a.y, z / a.z };
    }
    inline Vector3 operator+(float f) const
    {
        return { x + f, y + f, z + f };
    }
    inline Vector3 operator-(float f) const
    {
        return { x - f, y - f, z - f };
    }
    inline Vector3 operator*(float f) const
    {
        return { x * f, y * f, z * f };
    }
    inline Vector3 operator/(float f) const
    {
        return { x / f, y / f, z / f };
    }
    inline void operator+=(const Vector3& a)
    {
        x += a.x;
        y += a.y;
        z += a.z;
    }
    inline void operator-=(const Vector3& a)
    {
        x -= a.x;
        y -= a.y;
        z -= a.z;
    }
    inline void operator*=(const Vector3& a)
    {
        x *= a.x;
        y *= a.y;
        z *= a.z;
    }
    inline void operator/=(const Vector3& a)
    {
        x /= a.x;
        y /= a.y;
        z /= a.z;
    }
    inline void operator+=(float a)
    {
        x += a;
        y += a;
        z += a;
    }
    inline void operator-=(float a)
    {
        x += a;
        y += a;
        z += a;
    }
    inline void operator*=(float a)
    {
        x *= a;
        y *= a;
        z *= a;
    }
    inline void operator/=(float a)
    {
        x /= a;
        y /= a;
        z /= a;
    }

    inline Vector3 cross(const Vector3& from) const
    {
        return { (y * from.z) - (z * from.y), (z * from.x) - (x * from.z), (x * from.y) - (y * from.x) };
    }
    inline T dot(const Vector3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }
    inline T squaredLength() const
    {
        return x * x + y * y + z * z;
    }
    inline T length() { return std::sqrt(squaredLength()); }
    inline Vector3 normalize() const
    {
        Vector3 normalized = *this;
        const T len = normalized.length();
        if (len > 0) {
            const T inv_len = 1 / len;
            normalized.x *= inv_len;
            normalized.y *= inv_len;
            normalized.z *= inv_len;
        }
        return normalized;
    }

    std::string toString()
    {
        std::string val = std::to_string(x);
        val.append(" ");
        val.append(std::to_string(y));
        val.append(" ");
        val.append(std::to_string(z));
        return val;
    }
};

template <class T>
struct Quat {
    T x, y, z, w;
};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;

typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;

typedef Quat<float> Quatf;

}