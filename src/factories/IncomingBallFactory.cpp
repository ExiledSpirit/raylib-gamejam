#include "IncomingBallFactory.hpp"

#include "../components/IncomingBall.hpp"
#include "../components/Transform2D.hpp"

#include <ecs/components/Sprite.hpp>
#include "../resources/asset/AssetManager.hpp"

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

    entt::entity entity = world.registry.create();

    auto& transform = world.registry.emplace<Transform2D>(entity);
    transform.position = Vector2{144.0f, -16.0f};
    transform.rotation = 0.0f;
    transform.scale = Vector2{1.0f, 1.0f};
    transform.origin = Vector2{5.0f, 5.0f};

    auto& incoming = world.registry.emplace<IncomingBall>(entity);
    incoming.velocity = Vector2{0.0f, 180.0f};
    incoming.radius = 5.0f;
    incoming.groundY = 248.0f;
    incoming.active = true;

    auto& sprite = world.registry.emplace<Sprite>(entity);
    sprite.albedoTexture = &assets.GetTexture("ball");
    sprite.source = Rectangle{0.0f, 0.0f, 16.0f, 16.0f};

    return entity;
}
