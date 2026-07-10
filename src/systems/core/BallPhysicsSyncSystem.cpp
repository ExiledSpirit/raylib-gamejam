#include "BallPhysicsSyncSystem.hpp"

#include "../../components/Ball.hpp"
#include "../../components/BallPhysicsBody.hpp"
#include "../../components/Transform2D.hpp"
#include "../../resources/TileMapResource.hpp"

#include <box2d/box2d.h>

#include <cmath>

static Vector2 PhysicsToWorldPixels(
    const TileMapResource& map,
    b2Vec2 positionMeters
)
{
    return Vector2{
        map.origin.x + positionMeters.x * static_cast<float>(TILE_SIZE),
        map.origin.y + positionMeters.y * static_cast<float>(TILE_SIZE)
    };
}

void BallPhysicsSyncSystem(World& world)
{
    auto& map =
        world.GetResource<TileMapResource>();

    auto view =
        world.registry.view<Ball, BallPhysicsBody, Transform2D>();

    for(auto [entity, ball, physicsBody, transform] : view.each())
    {
        if(!b2Body_IsValid(physicsBody.bodyId))
        {
            continue;
        }

        b2Vec2 position =
            b2Body_GetPosition(physicsBody.bodyId);

        transform.position =
            PhysicsToWorldPixels(map, position);

        b2Rot rotation =
            b2Body_GetRotation(physicsBody.bodyId);

        transform.rotation =
            std::atan2(rotation.s, rotation.c);
    }
}