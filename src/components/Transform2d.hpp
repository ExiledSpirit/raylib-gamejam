#pragma once

#include <raylib.h>

struct Transform2D
{
    // Position in internal game pixels, not Box2D meters.
    // Example: 320x180 game space.
    Vector2 position{0.0f, 0.0f};

    // Store rotation in radians because Box2D uses radians.
    // Convert to degrees only when drawing with raylib.
    float rotation = 0.0f;

    // Visual scale. Usually {1, 1} for pixel art.
    Vector2 scale{1.0f, 1.0f};

    // Local origin/pivot in pixels.
    // For a ball, this is usually {radius, radius} or {0, 0}
    // depending on how you draw it.
    Vector2 origin{0.0f, 0.0f};
};