#include "IncomingBallFactory.hpp"

#include "../components/IncomingBall.hpp"
#include "../components/Transform2D.hpp"

#include <ecs/components/Sprite.hpp>
#include "../resources/asset/AssetManager.hpp"
#include "../resources/TileMapResource.hpp"
#include <box2d/box2d.h>

static Vector2 ArenaToWorldPixels(
    const TileMapResource& map,
    b2Vec2 positionMeters
)
{
    return Vector2{
        map.origin.x + positionMeters.x * static_cast<float>(TILE_SIZE),
        map.origin.y + positionMeters.y * static_cast<float>(TILE_SIZE)
    };
}

void DestroyIncomingBalls(World& world)
{
    auto view = world.registry.view<IncomingBall>();

    for(auto entity : view)
    {
        world.registry.destroy(entity);
    }
}

entt::entity CreateIncomingBall(World& world)
{
    DestroyIncomingBalls(world);

    auto& assets = world.GetResource<AssetManager>();
    auto& map = world.GetResource<TileMapResource>();

    entt::entity entity = world.registry.create();

    auto positionMeters = b2Vec2{3.0f, 0.0f};
    Vector2 positionPixels = ArenaToWorldPixels(map, positionMeters);

    auto& transform = world.registry.emplace<Transform2D>(entity);
    transform.position = positionPixels;
    transform.rotation = 0.0f;
    transform.scale = Vector2{1.0f, 1.0f};
    transform.origin = Vector2{5.0f, 5.0f};

    auto& incoming = world.registry.emplace<IncomingBall>(entity);
    incoming.velocity = Vector2{0.0f, 180.0f};
    incoming.radius = 5.0f;
    incoming.groundY = 310.0f;
    incoming.active = true;

    auto& sprite = world.registry.emplace<Sprite>(entity);
    sprite.albedoTexture = &assets.GetTexture("ball");
    sprite.source = Rectangle{0.0f, 0.0f, 16.0f, 16.0f};

    return entity;
}
