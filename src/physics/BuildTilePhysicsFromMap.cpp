#include "BuildTilePhysicsFromMap.hpp"

#include <physics/PhysicsWorldResource.hpp>

#include "../resources/TileMapResource.hpp"

#include <box2d/box2d.h>

static b2BodyId CreateStaticTileRect(
    b2WorldId worldId,
    int x,
    int y,
    int width,
    int height
)
{
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_staticBody;

    bodyDef.position = b2Vec2{
        static_cast<float>(x) + static_cast<float>(width) * 0.5f,
        static_cast<float>(y) + static_cast<float>(height) * 0.5f
    };

    b2BodyId bodyId =
        b2CreateBody(worldId, &bodyDef);

    b2ShapeDef shapeDef =
        b2DefaultShapeDef();

    shapeDef.material.friction = 0.4f;
    shapeDef.material.restitution = 0.9f;

    // Important if your wall hit system uses Box2D hit events.
    shapeDef.enableHitEvents = true;

    b2Polygon box =
        b2MakeBox(
            static_cast<float>(width) * 0.5f,
            static_cast<float>(height) * 0.5f
        );

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

    CreateStaticTileRect(
        physics.worldId,
        0,
        0,
        map.width,
        1
    );

    CreateStaticTileRect(
        physics.worldId,
        0,
        map.height - 1,
        map.width,
        1
    );

    CreateStaticTileRect(
        physics.worldId,
        0,
        1,
        1,
        map.height - 2
    );

    CreateStaticTileRect(
        physics.worldId,
        map.width - 1,
        1,
        1,
        map.height - 2
    );
}