#include "TileUtils.hpp"
#include <raylib.h>
#include <math.h>
// #include "CollisionUtils.hpp"

// Rectangle GetTileBounds(
//     const TileMapResource& map,
//     int tileX,
//     int tileY,
//     int tileSize
// ) {
//     Vector2 pos =
//     TileToWorld(map, tileX, tileY);

//     return {
//         pos.x,
//         pos.y,
//         TILE_SIZE,
//         TILE_SIZE
//     };
// }

// bool IsCollidingWithSolidTile(
//     const Rectangle& bounds,
//     const TileMapResource map
// ) {
//     Vector2 tilePos =
//     WorldToTile(
//         map,
//         {
//             bounds.x,
//             bounds.y
//         }
//     );
//     int left = (int)floor((bounds.x - map.origin.x) / TILE_SIZE);
//     int right = (int)floor((bounds.x - map.origin.x +  bounds.width - 1) / TILE_SIZE);
//     int top = (int)floor((bounds.y - map.origin.y) / TILE_SIZE);
//     int bottom = (int)floor((bounds.y - map.origin.y + bounds.height - 1) / TILE_SIZE);
//     for (int y = top; y <= bottom; y++)
//     {
//         for (int x = left; x <= right; x++)
//         {
//             if (x < 0 || y < 0 || x >= map.width || y >= map.height)
//             {
//                 continue;
//             }
//             // The tile is within the entity range

//             auto& tile = map.Get(x,y);

//             if (tile.id == TileId::Empty) continue;
//             // The tile is not empty

//             Rectangle tileBounds = GetTileBounds(map, x, y, TILE_SIZE);

//             auto collision = ResolveAABB(bounds, tileBounds);

//             if (collision && collision.value().penetration != 0) return true;
//             // It does collides with our entity
//         }
//     }

//     return false;
// }

Vector2 TileToWorld(
    const TileMapResource& map,
    int tileX,
    int tileY)
{
    return Vector2{
        map.origin.x + tileX * TILE_SIZE,
        map.origin.y + tileY * TILE_SIZE
    };
}

Vector2 WorldToTile(
    const TileMapResource& map,
    Vector2 worldPos)
{
    return {
        floor((worldPos.x - map.origin.x) / TILE_SIZE),
        floor((worldPos.y - map.origin.y) / TILE_SIZE)
    };
}
