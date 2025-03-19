#include <gtest/gtest.h>
#include "Segment3D.h"
#include <cmath>

TEST(Segment3D_Cases, Intersect_Inside)
{
    Segment3D segA({0, 0, 0}, {5, 0, 0});
    Segment3D segB({3, -1, 0}, {3, 2, 0});
    EXPECT_DOUBLE_EQ(segA.distanceTo(segB), 0.0);
}

TEST(Segment3D_Cases, Intersection_At_Endpoint)
{
    Segment3D segA({0, 0, 0}, {2, 0, 0});
    Segment3D segB({2, 0, 0}, {2, 2, 0});
    EXPECT_DOUBLE_EQ(segA.distanceTo(segB), 0.0);
}

TEST(Segment3D_Cases, Collinear_Overlap)
{
    Segment3D segA({0, 0, 0}, {5, 0, 0});
    Segment3D segB({3, 0, 0}, {8, 0, 0});
    EXPECT_DOUBLE_EQ(segA.distanceTo(segB), 0.0);
}

TEST(Segment3D_Cases, Collinear_No_Overlap)
{
    Segment3D segA({0, 0, 0}, {3, 0, 0});
    Segment3D segB({4, 0, 0}, {8, 0, 0});
    EXPECT_DOUBLE_EQ(segA.distanceTo(segB), 1.0);
}

TEST(Segment3D_Cases, Parallel_Separate)
{
    Segment3D segA({0, 0, 0}, {4, 0, 0});
    Segment3D segB({0, 1, 0}, {4, 1, 0});
    EXPECT_DOUBLE_EQ(segA.distanceTo(segB), 1.0);
}

TEST(Segment3D_Cases, Perpendicular_Intersect)
{
    Segment3D segA({0, 0, 0}, {4, 0, 0});
    Segment3D segB({2, -2, 0}, {2, 2, 0});
    EXPECT_DOUBLE_EQ(segA.distanceTo(segB), 0.0);
}

TEST(Segment3D_Cases, Perpendicular_Separate)
{
    Segment3D segA({0, 0, 0}, {4, 0, 0});
    Segment3D segB({5, -2, 0}, {5, 2, 0});
    EXPECT_DOUBLE_EQ(segA.distanceTo(segB), 1.0);
}

TEST(Segment3D_Cases, Skew_No_Intersect)
{
    Segment3D segA({0, 0, 0}, {0, 0, 4});
    Segment3D segB({1, 1, 0}, {2, 2, 2});
    EXPECT_NEAR(segA.distanceTo(segB), std::sqrt(2.0), 1e-5);
}

TEST(Segment3D_Cases, Point_Segment_Distance)
{
    Segment3D segA({2, 2, 2}, {2, 2, 2});
    Segment3D segB({0, 0, 0}, {1, 1, 1});
    EXPECT_NEAR(segA.distanceTo(segB), std::sqrt(3.0), 1e-5);
}

TEST(Segment3D_Cases, Negative_Coords_Intersect)
{
    Segment3D segA({-1, 0, 0}, {1, 0, 0});
    Segment3D segB({0, -1, 1}, {0, 1, -1});
    EXPECT_DOUBLE_EQ(segA.distanceTo(segB), 0.0);
}

TEST(Segment3D_Cases, Both_Points_Overlap)
{
    Segment3D segA({5, 5, 5}, {5, 5, 5});
    Segment3D segB({5, 5, 5}, {5, 5, 5});
    EXPECT_DOUBLE_EQ(segA.distanceTo(segB), 0.0);
}

TEST(Segment3D_Cases, Both_Points_Separate)
{
    Segment3D segA({1, 1, 1}, {1, 1, 1});
    Segment3D segB({3, 2, 1}, {3, 2, 1});
    EXPECT_NEAR(segA.distanceTo(segB), std::sqrt(5.0), 1e-5);
}

TEST(Segment3D_Cases, Cross_Intersection)
{
    Segment3D segA({0, 0, 2}, {2, 2, 2});
    Segment3D segB({0, 2, 2}, {2, 0, 2});
    EXPECT_DOUBLE_EQ(segA.distanceTo(segB), 0.0);
}

TEST(Segment3D_Cases, Endpoint_Overlap)
{
    Segment3D segA({2, 2, 2}, {4, 4, 4});
    Segment3D segB({4, 4, 4}, {5, 5, 5});
    EXPECT_DOUBLE_EQ(segA.distanceTo(segB), 0.0);
}

TEST(Segment3D_Cases, Skew_Far_Separate)
{
    Segment3D segA({0, 0, 0}, {1, 1, 1});
    Segment3D segB({2, 2, 2}, {3, 3, 4});
    EXPECT_GT(segA.distanceTo(segB), 1.5);
}

TEST(Segment3D_Cases, Collinear_Negative_Overlap)
{
    Segment3D segA({-5, 0, 0}, {-1, 0, 0});
    Segment3D segB({-3, 0, 0}, {2, 0, 0});
    EXPECT_DOUBLE_EQ(segA.distanceTo(segB), 0.0);
}

TEST(Segment3D_Cases, Segment_Within_Segment)
{
    Segment3D segA({1, 1, 1}, {10, 1, 1});
    Segment3D segB({3, 1, 1}, {7, 1, 1});
    EXPECT_DOUBLE_EQ(segA.distanceTo(segB), 0.0);
}

TEST(Segment3D_Cases, Parallel_Separate_Along_Y)
{
    Segment3D segA({0, 0, 0}, {0, 5, 0});
    Segment3D segB({1, 2, 0}, {1, 7, 0});
    EXPECT_DOUBLE_EQ(segA.distanceTo(segB), 1.0);
}

TEST(Segment3D_Cases, Endpoint_Overlap_Skew)
{
    Segment3D segA({0, 0, 0}, {1, 1, 2});
    Segment3D segB({1, 1, 2}, {2, 2, 4});
    EXPECT_DOUBLE_EQ(segA.distanceTo(segB), 0.0);
}

TEST(Segment3D_Cases, Parallel_X_Separate_By_2)
{
    Segment3D segA({10, 0, 0}, {20, 0, 0});
    Segment3D segB({10, 2, 0}, {20, 2, 0});
    EXPECT_DOUBLE_EQ(segA.distanceTo(segB), 2.0);
}
