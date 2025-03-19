#pragma once

#include "Point3D.h"
#include "Vector3D.h"

class Segment3D
{
public:
  Segment3D() = default;
  Segment3D(const Point3D &a, const Point3D &b)
      : p1(a), p2(b) {}

  double length() const;
  double distanceTo(const Segment3D &other) const;

private:
  bool pointOnSegment(const Point3D &P, const Point3D &A, const Point3D &B) const;
  bool intersects(const Segment3D &other) const;
  bool isCollinear(const Segment3D &other) const;
  bool isPerpendicular(const Segment3D &other) const;
  Point3D closestPointTo(const Point3D &p) const;

private:
  Point3D p1{};
  Point3D p2{};
};
