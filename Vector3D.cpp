#include "Vector3D.h"
#include <cmath>

double Vector3D::getX() const
{
    return x;
}

double Vector3D::getY() const
{
    return y;
}

double Vector3D::getZ() const
{
    return z;
}

double Vector3D::dot(const Vector3D &rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector3D Vector3D::cross(const Vector3D &rhs) const
{
    return Vector3D(
        y * rhs.z - z * rhs.y,
        z * rhs.x - x * rhs.z,
        x * rhs.y - y * rhs.x);
}

double Vector3D::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

Vector3D Vector3D::normalized() const
{
    const auto len = length();
    return (len == 0.0) ? Vector3D{} : Vector3D{x / len, y / len, z / len};
}
