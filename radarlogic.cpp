#include "radarlogic.h"

#include <cmath>

bool RadarLogic::isInsideSector(
    double x,
    double y,
    double radius,
    double heading,
    double alpha)
{
    double distance = std::sqrt(x * x + y * y);

    if (distance > radius)
        return false;

    double theta = std::atan2(y, x) * 180.0 / M_PI;

    if (theta < 0)
        theta += 360.0;

    double diff = theta - heading;

    while (diff > 180)
        diff -= 360;

    while (diff < -180)
        diff += 360;

    return std::abs(diff) <= alpha / 2.0;
}