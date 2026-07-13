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
    // This is the center point of the whole hittable area.
    // Adjust this offset until it visually matches the bat.
    Vector2 strikeCenter{
        strike.playerPosition.x + 8.0f,
        strike.playerPosition.y - 8.0f
    };

    constexpr float zoneWidth = 36.0f;

    constexpr float topHeight = 14.0f;
    constexpr float perfectHeight = 12.0f;
    constexpr float bottomHeight = 14.0f;

    const float totalHeight =
        topHeight + perfectHeight + bottomHeight;

    const float left =
        strikeCenter.x - zoneWidth * 0.5f;

    const float top =
        strikeCenter.y - totalHeight * 0.5f;

    strike.topZone = Rectangle{
        left,
        top,
        zoneWidth,
        topHeight
    };

    strike.perfectZone = Rectangle{
        left,
        top + topHeight,
        zoneWidth,
        perfectHeight
    };

    strike.bottomZone = Rectangle{
        left,
        top + topHeight + perfectHeight,
        zoneWidth,
        bottomHeight
    };
}