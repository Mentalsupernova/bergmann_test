#include "Point3D.h"
#include <cmath>

double Point3D::getX() const
{
    return x;
}

double Point3D::getY() const
{
    return y;
}

double Point3D::getZ() const
{
    return z;
}

double Point3D::distanceTo(const Point3D &other) const
{

    const auto dx = x - other.getX();
    const auto dy = y - other.getY();
    const auto dz = z - other.getZ();

    return std::sqrt(dx * dx + dy * dy + dz * dz);
}