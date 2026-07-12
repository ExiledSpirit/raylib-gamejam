#include "ArenaFactory.hpp"

#include "../components/Transform2d.hpp"
#include "../components/Arena.hpp"
#include "../resources/asset/AssetManager.hpp"
#include <ecs/components/Sprite.hpp>

entt::entity CreateArena(
    World& world
) {
    
    auto& assets = world.GetResource<AssetManager>();

    entt::entity entity =
        world.registry.create();

    Sprite sprite = Sprite{.pivot={.x=320.f, .y=180.f}};
    
    sprite.albedoTexture = &assets.GetTexture("arena");
    sprite.source = Rectangle{0.0f, 0.0f, 640.0f, 360.0f};
    world.registry.emplace<Sprite>(entity, sprite);

    auto& transform =
        world.registry.emplace<Transform2D>(entity);

    transform.position = {320.0f, 180.0f};
    transform.rotation = 0;
    transform.scale = Vector2{1.0f, 1.0f};
    transform.origin = Vector2{320.0f, 180.0f};

    world.registry.emplace<Arena>(entity);

    return entity;
}
