#pragma once

#include <core/World.hpp>
#include <ecs/components/Sprite.hpp>
#include "../../components/Transform2d.hpp"

void SpriteRenderSystem(World& world);
static void DrawSprite(
    const Transform2D& transform,
    const Sprite& sprite,
    Vector2 position
);