#include "TileRenderSystem.hpp"

#include "../../resources/TileMapResource.hpp"
#include "../../resources/TileDatabaseResource.hpp"
#include "../../utils/TileUtils.hpp"

#include <raylib.h>

void TileRenderSystem(World& world)
{
    auto& map =
        world.GetResource<TileMapResource>();

    auto& database =
        world.GetResource<TileDatabaseResource>();

    for(int y = 0; y < map.height; y++)
    {
        for(int x = 0; x < map.width; x++)
        {
            auto& tile =
                map.Get(x, y);

            if(tile.id == TileId::Empty)
            {
                continue;
            }

            auto& definition =
                database.definitions[tile.id];

            Vector2 worldPos =
                TileToWorld(map, x, y);

            DrawTexturePro(
                definition.texture,

                Rectangle{
                    0.0f,
                    0.0f,
                    static_cast<float>(definition.texture.width),
                    static_cast<float>(definition.texture.height)
                },

                Rectangle{
                    worldPos.x,
                    worldPos.y,
                    static_cast<float>(TILE_SIZE),
                    static_cast<float>(TILE_SIZE)
                },

                Vector2{
                    0.0f,
                    0.0f
                },

                0.0f,

                WHITE
            );
        }
    }
}