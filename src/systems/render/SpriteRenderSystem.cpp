#include "SpriteRenderSystem.hpp"

#include <core/World.hpp>

#include <algorithm>
#include <cmath>

#include "../../components/Transform2d.hpp"
#include "../../components/Background.hpp"
#include "../../components/Arena.hpp"
#include <ecs/components/Sprite.hpp>

static void DrawSprite(
    const Transform2D& transform,
    const Sprite& sprite,
    Vector2 position
);

void SpriteRenderSystem(World& world)
{
    auto spriteView =
        world.registry.view<Transform2D, Sprite>(entt::exclude<Background, Arena>);

    for(auto [entity, transform, sprite] : spriteView.each())
    {
        (void)entity;

        DrawSprite(
            transform,
            sprite,
            transform.position
        );
    }
}

static void DrawSprite(
    const Transform2D& transform,
    const Sprite& sprite,
    Vector2 position
)
{
    if(sprite.albedoTexture == nullptr)
    {
        TraceLog(
            LOG_ERROR,
            "Sprite has null albedoTexture"
        );

        return;
    }

    Rectangle source =
        sprite.source;

    if(source.width == 0.f || source.height == 0.f)
    {
        source = Rectangle{
            0.f,
            0.f,
            static_cast<float>(sprite.albedoTexture->width),
            static_cast<float>(sprite.albedoTexture->height)
        };
    }

    float frameWidth =
        std::abs(source.width);

    float frameHeight =
        std::abs(source.height);

    float textureWidth =
        static_cast<float>(sprite.albedoTexture->width);

    float textureHeight =
        static_cast<float>(sprite.albedoTexture->height);

    if(frameWidth <= 0.f || frameHeight <= 0.f)
    {
        return;
    }

    if(frameWidth > textureWidth)
    {
        frameWidth = textureWidth;
    }

    if(frameHeight > textureHeight)
    {
        frameHeight = textureHeight;
    }

    source.x =
        std::clamp(
            source.x,
            0.f,
            textureWidth - frameWidth
        );

    source.y =
        std::clamp(
            source.y,
            0.f,
            textureHeight - frameHeight
        );

    source.width =
        frameWidth;

    source.height =
        frameHeight;

    Rectangle dest{
        std::floor(position.x),
        std::floor(position.y),
        frameWidth * transform.scale.x,
        frameHeight * transform.scale.y
    };

    Vector2 origin{
        sprite.pivot.x * transform.scale.x,
        sprite.pivot.y * transform.scale.y
    };

    DrawTexturePro(
        *sprite.albedoTexture,
        source,
        dest,
        origin,
        transform.rotation,
        WHITE
    );
}