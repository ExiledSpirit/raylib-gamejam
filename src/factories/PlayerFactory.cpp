#include "PlayerFactory.hpp"

#include "../components/Player.hpp"
#include "../components/Transform2D.hpp"
#include "../components/animation/AnimationPlayer.hpp"
#include "../resources/TileMapResource.hpp"
#include <ecs/components/Sprite.hpp>

#include <raylib.h>

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
entt::entity CreatePlayer(
    World& world,
    b2Vec2 positionMeters,
    float facingRadians
)
{
    auto& map = world.GetResource<TileMapResource>();

    Vector2 positionPixels =
        ArenaToWorldPixels(map, positionMeters);

    entt::entity entity =
        world.registry.create();

    world.registry.emplace<Player>(entity);
    world.registry.emplace<Sprite>(entity);
    world.registry.emplace<AnimationPlayer>(entity);

    auto& transform =
        world.registry.emplace<Transform2D>(entity);

    transform.position = positionPixels;
    transform.rotation = facingRadians;
    transform.scale = Vector2{1.0f, 1.0f};
    transform.origin = Vector2{0.0f, 0.0f};

    auto& strike =
        world.GetResource<PlayerStrikeResource>();

    strike.playerPosition = positionPixels;
    strike.facingRadians = facingRadians;
    RebuildStrikeZones(strike);

    return entity;
}
