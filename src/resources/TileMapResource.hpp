#pragma once

#include <raylib.h>
#include <cstdint>
#include <vector>

constexpr int TILE_SIZE = 16;

enum class TileId : std::uint8_t
{
    Empty,
    Wall
};

struct Tile
{
    TileId id = TileId::Empty;
    bool solid;
};

struct TileMapResource
{
    int width = 20;
    int height = 15;

    Vector2 origin = {96.0f, 24.0f};

    std::vector<Tile> tiles;
    Vector2 center;

    Tile& Get(int x, int y)
    {
        return tiles[y * width + x];
    }

    const Tile& Get(int x, int y) const
    {
        return tiles[y * width + x];
    }
};
