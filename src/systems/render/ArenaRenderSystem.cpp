#include "ArenaRenderSystem.hpp"

#include "../../components/Arena.hpp"
#include "../../components/Transform2d.hpp"

#include <ecs/components/Sprite.hpp>

void ArenaRenderSystem(World& world)
{
    auto view =
        world.registry.view<Arena, Transform2D, Sprite>();

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