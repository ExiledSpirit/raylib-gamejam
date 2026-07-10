#pragma once

#include <box2d/box2d.h>

namespace CodeArena
{
    constexpr float WidthMeters = 20.0f;
    constexpr float HeightMeters = 15.0f;

    constexpr b2Vec2 PlayerPosition{2.0f, 12.0f};

    constexpr float PlayerFacingRadians = -0.45f;

    constexpr b2Vec2 BallPosition{3.0f, 12.0f};

    constexpr float BallRadius = 0.25f;
}
