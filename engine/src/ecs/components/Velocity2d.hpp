#pragma once

#include <raylib.h>

struct Velocity2D {
    Vector2 value;
    Vector2 target; // so controller system can communicate intentions with movement system
};
