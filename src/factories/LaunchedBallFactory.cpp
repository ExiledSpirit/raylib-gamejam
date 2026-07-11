#include "LaunchedBallFactory.hpp"

#include "../components/Ball.hpp"
#include "../components/BallPhysicsBody.hpp"
#include "../components/ShotScore.hpp"
#include "../components/Transform2D.hpp"

#include "../resources/StrikeZonesResource.hpp"
#include "../resources/TileMapResource.hpp"

#include <physics/PhysicsWorldResource.hpp>

#include <ecs/components/Sprite.hpp>
#include <resources/asset/AssetManager.hpp>

#include "../utils/PhaseHelper.hpp"

#include <box2d/box2d.h>
#include <raylib.h>

#include <cmath>

static b2Vec2 WorldPixelsToPhysicsMeters(
    const TileMapResource& map,
    Vector2 positionPixels
)
{
    return b2Vec2{
        (positionPixels.x - map.origin.x) / static_cast<float>(TILE_SIZE),
        (positionPixels.y - map.origin.y) / static_cast<float>(TILE_SIZE)
    };
}

static Vector2 PhysicsMetersToWorldPixels(
    const TileMapResource& map,
    b2Vec2 positionMeters
)
{
    return Vector2{
        map.origin.x + positionMeters.x * static_cast<float>(TILE_SIZE),
        map.origin.y + positionMeters.y * static_cast<float>(TILE_SIZE)
    };
}

static b2BodyId CreateBallBody(
    b2WorldId worldId,
    b2Vec2 positionMeters,
    float radiusMeters
)
{
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = positionMeters;

    // bodyDef.linearDamping = 0.18f;
    // bodyDef.angularDamping = 0.8f;
    bodyDef.linearDamping = 0.7f;
    bodyDef.angularDamping = 0.3f;

    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

    b2ShapeDef shapeDef = b2DefaultShapeDef();

    // shapeDef.density = 1.0f;
    // shapeDef.material.friction = 0.2f;
    // shapeDef.material.restitution = 0.9f;    
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.1f;
    shapeDef.material.restitution = 1.0f;

    shapeDef.enableContactEvents = true;
    shapeDef.enableHitEvents = true;



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

entt::entity CreateLaunchedBallFromStrike(World& world)
{
    DestroyActiveBalls(world);
    auto& physics = world.GetResource<PhysicsWorldResource>();
    auto& map = world.GetResource<TileMapResource>();
    auto& strike = world.GetResource<PlayerStrikeResource>();
    auto& assets = world.GetResource<AssetManager>();

    constexpr float ballRadiusMeters = 0.5f;

    b2Vec2 spawnPositionMeters =
        WorldPixelsToPhysicsMeters(
            map,
            strike.struckBallPosition
        );

    b2BodyId bodyId =
        CreateBallBody(
            physics.worldId,
            spawnPositionMeters,
            ballRadiusMeters
        );

    float finalPower =
        strike.basePower * strike.finalPowerMultiplier;

    b2Vec2 impulse{
        std::cos(strike.facingRadians) * finalPower,
        std::sin(strike.facingRadians) * finalPower
    };

    b2Body_ApplyLinearImpulseToCenter(
        bodyId,
        impulse,
        true
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
        PhysicsMetersToWorldPixels(
            map,
            spawnPositionMeters
        );

    transform.rotation = 0.0f;
    transform.scale = Vector2{1.0f, 1.0f};
    transform.origin = Vector2{8.0f, 8.0f};

    auto& sprite =
        world.registry.emplace<Sprite>(entity);

    sprite.albedoTexture = &assets.GetTexture("ball");
    sprite.source = Rectangle{0.0f, 0.0f, 16.0f, 16.0f};

    auto& score =
        world.registry.emplace<ShotScore>(entity);

    score.previousPosition = transform.position;
    score.initialized = true;

    return entity;
}
