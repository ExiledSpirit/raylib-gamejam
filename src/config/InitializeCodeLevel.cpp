#include "InitializeCodelevel.hpp"

#include "CodeArena.hpp"
#include "../resources/ArenaResource.hpp"
#include "../resources/TileMapResource.hpp"
#include "../physics/BuildTilePhysicsFromMap.hpp"
#include "../factories/BallFactory.hpp"
#include "../factories/PlayerFactory.hpp"

static void CreateCodeTileMap(World& world)
{
    auto& map = world.InsertResource<TileMapResource>();

    map.width = 20;
    map.height = 15;
    map.origin = Vector2{96.0f, 24.0f};

    map.tiles.resize(map.width * map.height);

    for(int y = 0; y < map.height; ++y)
    {
        for(int x = 0; x < map.width; ++x)
        {
            Tile& tile = map.Get(x, y);

            bool isBorder =
                x == 0 ||
                y == 0 ||
                x == map.width - 1 ||
                y == map.height - 1;

            tile.id = isBorder
                ? TileId::Wall
                : TileId::Empty;
        }
    }
}

void InitializeCodeLevel(World& world)
{
    CreateCodeTileMap(world);

    BuildTilePhysicsFromMap(world);

    CreatePlayer(world, b2Vec2{3.0f, 12.0f}, -0.45f);

    CreateBall(
        world,
        b2Vec2{3.0f, 12.0f}
    );
}
