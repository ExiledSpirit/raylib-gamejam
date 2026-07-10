#pragma once

#include <core/World.hpp>

#include <box2d/box2d.h>
#include <entt/entt.hpp>
#include "../resources/StrikeZonesResource.hpp"

entt::entity CreatePlayer(
    World& world,
    b2Vec2 positionMeters,
    float facingRadians
);

inline void RebuildStrikeZones(PlayerStrikeResource& strike)
{
    const float x = strike.playerPosition.x;
    const float y = strike.playerPosition.y;

    strike.topZone = Rectangle{x, y, 22.0f, 8.0f};
    strike.perfectZone = Rectangle{x, y + 8.0f, 22.0f, 7.0f};
    strike.bottomZone = Rectangle{x, y + 15.0f, 22.0f, 8.0f};
}