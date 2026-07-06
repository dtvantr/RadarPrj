#ifndef TARGET_H
#define TARGET_H

enum class TargetType {
    None,
    Safe,
    Considered,
    Danger
};

struct Target
{
    int id = 0;

    float x = 0.0f;
    float y = 0.0f;

    TargetType type = TargetType::None;

    double latitude;
    double longitude;

    float vx = 0.0f;
    float vy = 0.0f;

    bool visible = false;
};



#endif