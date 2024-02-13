#ifndef TSPINST_POINT_HEADER
#define TSPINST_POINT_HEADER

#include<cmath>

using ecDistancT = long long;

class Point {
 public:

    long long x, y;
    int originalIndex;

    Point(long long x, long long y, int originalIndex) {
        this->x = x;
        this->y = y;
        this->originalIndex = originalIndex;
    }

    ecDistancT disance(Point& other) {
        long long dx, dy;
        dx = x - other.x;
        dy = y - other.y;
        double dec = sqrt(dx * dx + dy * dy);

        return (ecDistancT) (dec+0.5);
    }
};


#endif