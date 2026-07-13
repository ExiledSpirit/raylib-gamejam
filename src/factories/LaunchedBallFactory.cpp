#include "LaunchedBallFactory.hpp"

#include "../components/Ball.hpp"
#include "../components/BallPhysicsBody.hpp"
#include "../components/ShotScore.hpp"
#include "../components/Transform2D.hpp"

#include "../resources/StrikeZonesResource.hpp"
#include "../resources/TileMapResource.hpp"
#include "../resources/PlayerStatsResource.hpp"

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

    bodyDef.linearDamping = 0.7f;
    bodyDef.angularDamping = 0.3f;

    b2BodyId bodyId =
        b2CreateBody(worldId, &bodyDef);

    b2ShapeDef shapeDef =
        b2DefaultShapeDef();

    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.1f;
    shapeDef.material.restitution = 1.0f;

    shapeDef.enableContactEvents = true;
    shapeDef.enableHitEvents = true;

    // Important for multi-ball:
    // negative group index means balls in this same group do NOT collide with each other.
    // They will still collide with walls, because walls should use groupIndex = 0.
    shapeDef.filter.groupIndex = -1;

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

static entt::entity CreateOneLaunchedBall(
    World& world,
    Vector2 spawnPositionPixels,
    float angleRadians,
    float speed,
    float radiusMeters
)
{
    auto& physics =
        world.GetResource<PhysicsWorldResource>();

    auto& map =
        world.GetResource<TileMapResource>();

    auto& assets =
        world.GetResource<AssetManager>();

    auto& stats =
        world.GetResource<PlayerStatsResource>();

    b2Vec2 spawnPositionMeters =
        WorldPixelsToPhysicsMeters(
            map,
            spawnPositionPixels
        );

    b2BodyId bodyId =
        CreateBallBody(
            physics.worldId,
            spawnPositionMeters,
            radiusMeters
        );

    b2Vec2 velocity{
        std::cos(angleRadians) * speed,
        std::sin(angleRadians) * speed
    };

    // For your arcade game, this is better than impulse.
    // The finalPower becomes the actual ball speed.
    b2Body_SetLinearVelocity(
        bodyId,
        velocity
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
    transform.origin = Vector2{8.0f, 8.0f};

    float radiusPixels =
        radiusMeters * static_cast<float>(TILE_SIZE);

    float diameterPixels =
        radiusPixels * 2.0f;

    // Your ball sprite source is 16x16.
    // If radiusMeters = 0.5 and TILE_SIZE = 16:
    // diameter = 16px, scale = 1.
    transform.scale = Vector2{
        diameterPixels / 16.0f,
        diameterPixels / 16.0f
    };

    auto& sprite =
        world.registry.emplace<Sprite>(entity);

    sprite.albedoTexture =
        &assets.GetTexture("ball");

    sprite.source =
        Rectangle{0.0f, 0.0f, 16.0f, 16.0f};

    auto& score =
        world.registry.emplace<ShotScore>(entity);

    score.previousPosition = transform.position;
    score.initialized = true;

    if(stats.HasExplosiveBounce())
    {
        // world.registry.emplace<ExplosiveBounceEffect>(
        //     entity,
        //     stats.explosionChanceOnWallBounce,
        //     stats.explosionVelocityMultiplier
        // );
    }

    return entity;
}

entt::entity CreateLaunchedBallFromStrike(World& world)
{
    DestroyActiveBalls(world);

    auto& strike =
        world.GetResource<PlayerStrikeResource>();

    auto& stats =
        world.GetResource<PlayerStatsResource>();

    int ballCount =
        stats.GetLaunchedBallCount();

    float radiusMeters =
        stats.GetBallRadiusMeters();

    float finalPower =
        strike.basePower * strike.finalPowerMultiplier;

    entt::entity firstEntity =
        entt::null;

    float centerIndex =
        static_cast<float>(ballCount - 1) * 0.5f;

    for(int i = 0; i < ballCount; ++i)
    {
        float angleOffset =
            (static_cast<float>(i) - centerIndex) *
            stats.multiBallAngleStep;

        float angle =
            strike.facingRadians + angleOffset;

        entt::entity entity =
            CreateOneLaunchedBall(
                world,
                strike.struckBallPosition,
                angle,
                finalPower,
                radiusMeters
            );

        if(firstEntity == entt::null)
        {
            firstEntity = entity;
        }
    }

    return firstEntity;
}