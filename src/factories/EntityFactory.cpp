#include "EntityFactory.hpp"
#include "../components/animation/AnimationPlayer.hpp"
#include "../components/TriggerCollider.hpp"
#include "../components/Destroyable.hpp"
#include "../const/AnimationIds.hpp"

entt::entity CreatePlayerEntity(
    World& world,
    Sprite sprite,
    Transform2D transform,
    BoxCollider2D boxCollider
)
{
    auto player = world.registry.create();

    world.registry.emplace<Sprite>(player, sprite);
    world.registry.emplace<Transform2D>(player, transform);
    world.registry.emplace<BoxCollider2D>(player, boxCollider);

    world.registry.emplace<AnimationPlayer>(player);

    auto& assets = world.GetResource<AssetManager>();

    return player;
}
