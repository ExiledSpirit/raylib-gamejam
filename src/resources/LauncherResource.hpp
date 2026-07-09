#pragma once

#include <raylib.h>

struct LauncherResource
{
    Vector2 position{40.0f, 130.0f};

    float aimAngle = -0.65f;
    float aimSpeed = 2.5f;

    float power = 0.0f;
    float maxPower = 10.0f;
    float chargeSpeed = 7.0f;

    bool charging = false;
};