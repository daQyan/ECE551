#include "circle.hpp"

#include <cmath>
#include <algorithm>
#include <cstdlib>

  void Circle::move(double dx, double dy) {
    center.move(dx, dy);
  }

  double Circle::intersectionArea(const Circle & otherCircle) {

    double distance = center.distanceFrom(otherCircle.center);
    double r1 = radius;
    double r2 = otherCircle.radius;
    if (distance >= r1+r2) {
        return 0.0;
    }

    if (distance <= std::abs(r1 - r2)) {
        return M_PI * std::min(r1, r2) * std::min(r1, r2);
    }
    
    double a = acos((r1 * r1 - r2 * r2 + distance * distance) / (2 * distance * r1));
    double b = acos((r2 * r2 - r1 * r1 + distance * distance) / (2 * distance * r2));
    return a * r1 * r1 + b * r2 * r2 - distance * r1 * sin(a);
    
  }