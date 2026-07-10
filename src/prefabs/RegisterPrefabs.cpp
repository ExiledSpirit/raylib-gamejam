#include "RegisterPrefabs.hpp"

#include "../factories/EntityFactory.hpp"
#include "../resources/asset/AssetManager.hpp"
#include "../components/PrefabInstance.hpp"
#include "../components/animation/AnimationPlayer.hpp"
#include "../const/AnimationIds.hpp"

void RegisterPrefabs(
    World& world,
    PrefabRegistry& registry)
{
    registry.Register(
        PrefabDefinition{
            .id = "player",
            .displayName = "Player",
            .spawn = [](World& world, Vector2 position)
            {
                auto& assets = world.GetResource<AssetManager>();

                auto& idle = assets.GetAnimation(AnimationIds::PlayerIdle);

                Sprite sprite{
                    .albedoTexture = idle.texture,
                    .source = idle.frames.empty()
                        ? Rectangle{0.f, 0.f, 8.f, 8.f}
                        : idle.frames[0],
                    .pivot = {4.f, 4.f},
                    .flipX = false
                };

                auto entity = CreatePlayerEntity(
                    world,
                    sprite,
                    Transform2D{
                        .position = position,
                        .rotation = 0.f,
                        .scale = 1.f
                    },
                    BoxCollider2D{
                        .size = {8.f, 8.f},
                        .offset = {-4.f, -4.f}
                    }
                );

                auto& animation =
                    world.registry.get<AnimationPlayer>(entity);

                animation.currentClip = &idle;
                animation.currentFrame = 0;
                animation.timer = 0.f;
                animation.playing = true;

                world.registry.emplace<PrefabInstance>(
                    entity,
                    "player"
                );

                return entity;
            }
        });
}