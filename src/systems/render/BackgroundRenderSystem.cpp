#include "BackgroundRenderSystem.hpp"

#include "../../components/Background.hpp"
#include "../../components/Transform2d.hpp"

#include <ecs/components/Sprite.hpp>

void BackgroundRenderSystem(World& world)
{
    auto view =
        world.registry.view<Background, Transform2D, Sprite>();

    for(auto [entity, transform, sprite] : view.each())
    {
        (void)entity;

        // Use your existing sprite draw logic here.
        // Example:
        DrawTexturePro(
            *sprite.albedoTexture,
            sprite.source,
            Rectangle{
                transform.position.x,
                transform.position.y,
                sprite.source.width,
                sprite.source.height
            },
            transform.origin,
            transform.rotation,
            WHITE
        );
    }
}