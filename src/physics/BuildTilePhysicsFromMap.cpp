#include "BuildTilePhysicsFromMap.hpp"

#include <physics/PhysicsWorldResource.hpp>

#include "../resources/TileMapResource.hpp"

#include <box2d/box2d.h>

static b2BodyId CreateStaticBox(
    b2WorldId worldId,
    b2Vec2 center,
    float halfWidth,
    float halfHeight
)
{
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_staticBody;
    bodyDef.position = center;

    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.material.friction = 0.4f;
    shapeDef.material.restitution = 0.9f;

    b2Polygon box = b2MakeBox(halfWidth, halfHeight);

    b2CreatePolygonShape(
        bodyId,
        &shapeDef,
        &box
    );

    return bodyId;
}

void BuildTilePhysicsFromMap(World& world)
{
    auto& physics =
        world.GetResource<PhysicsWorldResource>();

    auto& map =
        world.GetResource<TileMapResource>();

    for(int y = 0; y < map.height; ++y)
    {
        for(int x = 0; x < map.width; ++x)
        {
            const Tile& tile = map.Get(x, y);

            if(tile.id != TileId::Wall)
            {
                continue;
            }

            CreateStaticBox(
                physics.worldId,
                b2Vec2{
                    static_cast<float>(x) + 0.5f,
                    static_cast<float>(y) + 0.5f
                },
                0.5f,
                0.5f
            );
        }
    }
}