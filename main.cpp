#include <iostream>
#include "Segment3D.h"

int main()
{

    Segment3D segA({10.0, 0.0, 0.0}, {20.0, 0.0, 0.0});
    Segment3D segB({10.0, 2.0, 0.0}, {20.0, 2.0, 0.0});
    double dist = segA.distanceTo(segB);
    std::cout << "distance = " << dist << std::endl;

    return 0;
}
