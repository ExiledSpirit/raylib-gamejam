#pragma once

#include <raylib.h>
#include <box2d/box2d.h>

struct ArenaResource
{
    float widthMeters = 20.0f;
    float heightMeters = 15.0f;

    float pixelsPerMeter = 16.0f;

    Vector2 originPixels{96.0f, 24.0f};

    Rectangle GetPixelRect() const
    {
        return Rectangle{
            originPixels.x,
            originPixels.y,
            widthMeters * pixelsPerMeter,
            heightMeters * pixelsPerMeter
        };
    }

    Vector2 ToPixels(b2Vec2 meters) const
    {
        return Vector2{
            originPixels.x + meters.x * pixelsPerMeter,
            originPixels.y + meters.y * pixelsPerMeter
        };
    }

    b2Vec2 ToMeters(Vector2 pixels) const
    {
        return b2Vec2{
            (pixels.x - originPixels.x) / pixelsPerMeter,
            (pixels.y - originPixels.y) / pixelsPerMeter
        };
    }
};