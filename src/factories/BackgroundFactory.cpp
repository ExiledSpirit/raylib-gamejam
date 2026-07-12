#include "BackgroundFactory.hpp"

#include "../components/Transform2d.hpp"
#include "../components/Background.hpp"
#include "../resources/asset/AssetManager.hpp"
#include <ecs/components/Sprite.hpp>

entt::entity CreateBackground(
    World& world
) {
    
    auto& assets = world.GetResource<AssetManager>();

    entt::entity entity =
        world.registry.create();

    Sprite sprite = Sprite{.pivot={.x=0.f, .y=0.f}};
    
    sprite.albedoTexture = &assets.GetTexture("background");
    sprite.source = Rectangle{0.0f, 0.0f, 640.0f, 360.0f};
    world.registry.emplace<Sprite>(entity, sprite);

    auto& transform =
        world.registry.emplace<Transform2D>(entity);

    transform.position = {0.0f, 0.0f};
    transform.rotation = 0;
    transform.scale = Vector2{1.0f, 1.0f};
    transform.origin = Vector2{0.0f, 0.0f};

    world.registry.emplace<Background>(entity);

    return entity;
}
