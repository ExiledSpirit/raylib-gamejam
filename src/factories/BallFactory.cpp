#include "BallFactory.hpp"

#include "../components/Ball.hpp"
#include "../components/BallPhysicsBody.hpp"
#include "../components/ShotScore.hpp"
#include "../components/Transform2D.hpp"
#include "../resources/TileMapResource.hpp"

#include <physics/PhysicsWorldResource.hpp>

#include <box2d/box2d.h>

static b2BodyId CreateBallBody(
    b2WorldId worldId,
    b2Vec2 positionMeters,
    float radiusMeters
)
{
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = positionMeters;
    bodyDef.linearDamping = 0.25f;
    bodyDef.angularDamping = 0.8f;

    b2BodyId bodyId = b2CreateBody(
        worldId,
        &bodyDef
    );

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.2f;
    shapeDef.material.restitution = 0.85f;

    b2Circle circle{};
    circle.center = b2Vec2{0.0f, 0.0f};
    circle.radius = radiusMeters;

    b2CreateCircleShape(
        bodyId,
        &shapeDef,
        &circle
    );

    return bodyId;
}

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

entt::entity CreateBall(
    World& world,
    b2Vec2 positionMeters
)
{
    auto& physics =
        world.GetResource<PhysicsWorldResource>();

    auto& map =
        world.GetResource<TileMapResource>();

    constexpr float radiusMeters = 0.25f;

    b2BodyId bodyId =
        CreateBallBody(
            physics.worldId,
            positionMeters,
            radiusMeters
        );

    entt::entity entity =
        world.registry.create();

    world.registry.emplace<Ball>(entity);
    world.registry.emplace<BallPhysicsBody>(
        entity,
        bodyId
    );

    auto& transform =
        world.registry.emplace<Transform2D>(entity);

    transform.position =
        PhysicsToWorldPixels(map, positionMeters);

    transform.rotation = 0.0f;

    world.registry.emplace<ShotScore>(entity);

    return entity;
}