#ifndef TARGET_H
#define TARGET_H

struct Target
{
    int id = 0;

    float x = 0.0f;
    float y = 0.0f;

    double latitude;
    double longitude;

    float vx = 0.0f;
    float vy = 0.0f;

    bool visible = false;
};

#endif