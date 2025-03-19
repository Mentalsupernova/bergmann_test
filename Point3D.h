#pragma once

class Point3D
{
public:
    Point3D() = default;
    Point3D(double x, double y, double z)
        : x(x), y(y), z(z) {}

    double getX() const;
    double getY() const;
    double getZ() const;

    double distanceTo(const Point3D &other) const;

private:
    double x{0.0}, y{0.0}, z{0.0};
};
