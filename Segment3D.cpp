#include "Segment3D.h"
#include <cmath>
#include <algorithm>

constexpr double EPSILON = 1e-9;

double Segment3D::length() const
{
    return p1.distanceTo(p2);
}

bool Segment3D::pointOnSegment(const Point3D &P,
                               const Point3D &A,
                               const Point3D &B) const
{
    Vector3D AB(A, B);
    Vector3D AP(A, P);

    Vector3D crossABAP = AB.cross(AP);
    double crossLen2 = crossABAP.dot(crossABAP);
    if (std::fabs(crossLen2) > EPSILON)
    {

        return false;
    }

    double denom = AB.dot(AB);
    if (denom < EPSILON)
    {
        double d = A.distanceTo(P);
        return (d < EPSILON);
    }

    double t = AP.dot(AB) / denom;
    return (t >= -EPSILON && t <= 1.0 + EPSILON);
}

bool Segment3D::intersects(const Segment3D &other) const
{

    if (pointOnSegment(p1, other.p1, other.p2))
    {
        return true;
    }
    if (pointOnSegment(p2, other.p1, other.p2))
    {
        return true;
    }
    if (pointOnSegment(other.p1, p1, p2))
    {
        return true;
    }
    if (pointOnSegment(other.p2, p1, p2))
    {
        return true;
    }

    Vector3D u(p1, p2);
    Vector3D v(other.p1, other.p2);

    Vector3D w(
        p1.getX() - other.p1.getX(),
        p1.getY() - other.p1.getY(),
        p1.getZ() - other.p1.getZ());

    Vector3D crossUv = u.cross(v);
    double denom = crossUv.dot(crossUv);

    if (std::fabs(denom) < EPSILON)
    {
        return false;
    }

    double a = u.dot(u);
    double b = u.dot(v);
    double c = v.dot(v);
    double d = u.dot(w);
    double e = v.dot(w);

    double denom2 = a * c - b * b;
    if (std::fabs(denom2) < EPSILON)
    {
        return false;
    }

    double t = (b * e - c * d) / denom2;
    double s = (a * e - b * d) / denom2;

    if (t < 0.0 || t > 1.0 || s < 0.0 || s > 1.0)
    {
        return false;
    }

    return true;
}

bool Segment3D::isCollinear(const Segment3D &other) const
{
    Vector3D u(p1, p2);
    Vector3D v(other.p1, other.p2);

    Vector3D crossUv = u.cross(v);
    double crossLen2 = crossUv.dot(crossUv);

    if (std::fabs(crossLen2) > EPSILON)
    {
        return false;
    }

    Vector3D w(p1, other.p1);
    Vector3D crossUw = u.cross(w);
    double crossLen2uw = crossUw.dot(crossUw);

    return (std::fabs(crossLen2uw) < EPSILON);
}

bool Segment3D::isPerpendicular(const Segment3D &other) const
{
    Vector3D u(p1, p2);
    Vector3D v(other.p1, other.p2);

    double dp = u.dot(v);
    return (std::fabs(dp) < EPSILON);
}

Point3D Segment3D::closestPointTo(const Point3D &p) const
{
    Vector3D u(p1, p2);
    Vector3D w2(p.getX() - p1.getX(), p.getY() - p1.getY(), p.getZ() - p1.getZ());

    double c1 = w2.dot(u);
    double c2 = u.dot(u);

    if (c2 < EPSILON)
    {
        return p1;
    }

    double t = c1 / c2;
    t = std::max(0.0, std::min(1.0, t));

    double rx = p1.getX() + u.getX() * t;
    double ry = p1.getY() + u.getY() * t;
    double rz = p1.getZ() + u.getZ() * t;

    return Point3D(rx, ry, rz);
}

double Segment3D::distanceTo(const Segment3D &other) const
{
    if (this->intersects(other))
    {
        return 0.0;
    }

    if (this->isCollinear(other))
    {
        Vector3D u(p1, p2);
        double lenU = u.length();
        if (lenU < EPSILON)
        {
            return p1.distanceTo(other.closestPointTo(p1));
        }

        auto projParam = [&](const Point3D &pt)
        {
            Vector3D w2(pt.getX() - p1.getX(), pt.getY() - p1.getY(), pt.getZ() - p1.getZ());
            return w2.dot(u) / (lenU * lenU);
        };

        double t1 = projParam(other.p1);
        double t2 = projParam(other.p2);
        double mn = std::min(t1, t2);
        double mx = std::max(t1, t2);

        if (mx < 0.0 || mn > 1.0)
        {
            double d1 = p1.distanceTo(other.closestPointTo(p1));
            double d2 = p2.distanceTo(other.closestPointTo(p2));
            double d3 = other.p1.distanceTo(this->closestPointTo(other.p1));
            double d4 = other.p2.distanceTo(this->closestPointTo(other.p2));
            return std::min({d1, d2, d3, d4});
        }
        else
        {
            return 0.0;
        }
    }

    Vector3D u(p1, p2);
    Vector3D v(other.p1, other.p2);
    Vector3D w(
        p1.getX() - other.p1.getX(),
        p1.getY() - other.p1.getY(),
        p1.getZ() - other.p1.getZ());

    double a = u.dot(u);
    double b = u.dot(v);
    double c = v.dot(v);
    double d = u.dot(w);
    double e = v.dot(w);

    double D = a * c - b * b;
    double sc, sN, sD = D;
    double tc, tN, tD = D;

    if (std::fabs(D) < EPSILON)
    {
        sN = 0.0;
        sD = 1.0;
        tN = d;
        tD = a;
    }
    else
    {
        sN = (b * d - a * e);
        tN = (c * d - b * e);
    }

    if (sN < 0.0)
    {
        sN = 0.0;
        tN = d;
        tD = a;
    }
    else if (sN > sD)
    {
        sN = sD;
        tN = d + b;
        tD = a;
    }

    if (tN < 0.0)
    {
        tN = 0.0;
    }
    else if (tN > tD)
    {
        tN = tD;
    }

    sc = (std::fabs(sN) < EPSILON ? 0.0 : sN / sD);
    tc = (std::fabs(tN) < EPSILON ? 0.0 : tN / tD);

    double pc1x = p1.getX() + u.getX() * tc;
    double pc1y = p1.getY() + u.getY() * tc;
    double pc1z = p1.getZ() + u.getZ() * tc;
    Point3D pc1(pc1x, pc1y, pc1z);

    double pc2x = other.p1.getX() + v.getX() * sc;
    double pc2y = other.p1.getY() + v.getY() * sc;
    double pc2z = other.p1.getZ() + v.getZ() * sc;
    Point3D pc2(pc2x, pc2y, pc2z);
    double distUniversal = pc1.distanceTo(pc2);
    double d1 = p1.distanceTo(other.closestPointTo(p1));
    double d2 = p2.distanceTo(other.closestPointTo(p2));
    double d3 = other.p1.distanceTo(this->closestPointTo(other.p1));
    double d4 = other.p2.distanceTo(this->closestPointTo(other.p2));

    return std::min({distUniversal, d1, d2, d3, d4});
}
