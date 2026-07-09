#pragma once

#include <box2d/box2d.h>
#include <raylib.h>

constexpr float PIXELS_PER_METER = 16.0f;

inline float ToMeters(float pixels)
{
    return pixels / PIXELS_PER_METER;
}

inline float ToPixels(float meters)
{
    return meters * PIXELS_PER_METER;
}

inline b2Vec2 ToMeters(Vector2 pixels)
{
    return b2Vec2{
        pixels.x / PIXELS_PER_METER,
        pixels.y / PIXELS_PER_METER
    };
}

inline Vector2 ToPixels(b2Vec2 meters)
{
    return Vector2{
        meters.x * PIXELS_PER_METER,
        meters.y * PIXELS_PER_METER
    };
}
