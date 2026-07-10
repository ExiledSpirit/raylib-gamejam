#pragma once

#include <core/World.hpp>
#include "../../resources/StrikeZonesResource.hpp"

static StrikeQuality GetStrikeQuality(
    Vector2 ballPosition,
    float radius,
    const PlayerStrikeResource& strike
);
static void LoseStrike(World& world);
void FallingBallStrikeSystem(World& world);
