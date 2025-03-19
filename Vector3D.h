#pragma once

#include "Point3D.h"

class Vector3D
{
public:
    Vector3D() = default;
    Vector3D(double x, double y, double z)
        : x(x), y(y), z(z) {}
    Vector3D(const Point3D &from, const Point3D &to)
        : x(to.getX() - from.getX()), y(to.getY() - from.getY()), z(to.getZ() - from.getZ()) {}

    double getX() const;
    double getY() const;
    double getZ() const;

    double dot(const Vector3D &rhs) const;
    Vector3D cross(const Vector3D &rhs) const;
    double length() const;
    Vector3D normalized() const;

    Vector3D operator*(double scalar) const
    {
        return Vector3D{x * scalar, y * scalar, z * scalar};
    }

    Vector3D operator+(const Vector3D &rhs) const
    {
        return Vector3D{x + rhs.x, y + rhs.y, z + rhs.z};
    }

    Vector3D operator-(const Vector3D &rhs) const
    {
        return Vector3D{x - rhs.x, y - rhs.y, z - rhs.z};
    }

private:
    double x{0.0}, y{0.0}, z{0.0};
};
