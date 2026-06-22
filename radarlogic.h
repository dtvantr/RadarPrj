#ifndef RADARLOGIC_H
#define RADARLOGIC_H

class RadarLogic
{
public:
    static bool isInsideSector(
        double x,
        double y,
        double radius,
        double heading,
        double alpha);
};

#endif