#pragma once

#include <raylib.h>
#include "../resources/TileMapResource.hpp"

Rectangle GetTileBounds(
    const TileMapResource& map,
    int tileX,
    int tileY,
    int tileSize
);

bool IsCollidingWithSolidTile(
    const Rectangle& bounds,
    const TileMapResource map
);

Vector2 TileToWorld(
    const TileMapResource& map,
    int tileX,
    int tileY);

Vector2 WorldToTile(
    const TileMapResource& map,
    Vector2 worldPos);
