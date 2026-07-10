#include "AnimationSystem.hpp"

#include "../../components/animation/AnimationPlayer.hpp"

#include <ecs/components/Sprite.hpp>
#include <ecs/resources/TimeResource.hpp>

#include <algorithm>

void AnimationSystem(World& world)
{
    auto view =
        world.registry.view<AnimationPlayer, Sprite>();

    for(auto [entity, animation, sprite] : view.each())
    {
        if(animation.currentClip == nullptr)
        {
            continue;
        }

        AnimationClip* clip =
            animation.currentClip;

        if(clip->frames.empty())
        {
            continue;
        }

        animation.timer +=
            world.GetResource<TimeResource>().deltaTime;

        while(animation.timer >= clip->frameDuration)
        {
            animation.timer -=
                clip->frameDuration;

            animation.currentFrame++;

            if(animation.currentFrame >= static_cast<int>(clip->frames.size()))
            {
                if(clip->loop)
                {
                    animation.currentFrame = 0;
                }
                else
                {
                    animation.currentFrame =
                        static_cast<int>(clip->frames.size()) - 1;
                }
            }
        }

        animation.currentFrame =
            std::clamp(
                animation.currentFrame,
                0,
                static_cast<int>(clip->frames.size()) - 1
            );

        sprite.albedoTexture =
            clip->texture;

        sprite.source =
            clip->frames[animation.currentFrame];
    }
}