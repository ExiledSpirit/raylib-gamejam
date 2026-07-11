#include "FloatingTextRenderSystem.hpp"

#include "../../components/FloatingText.hpp"
#include "../../components/Transform2D.hpp"

#include <raylib.h>
#include <algorithm>

void FloatingTextRenderSystem(World& world)
{
    auto view = world.registry.view<FloatingText, Transform2D>();

    for(auto [entity, text, transform] : view.each())
    {
        (void)entity;

        float t = text.age / text.lifetime;
        float alpha = 1.0f - std::clamp(t, 0.0f, 1.0f);

        Color color = text.color;
        color.a = static_cast<unsigned char>(255.0f * alpha);

        DrawText(
            text.text.c_str(),
            static_cast<int>(transform.position.x),
            static_cast<int>(transform.position.y),
            text.fontSize,
            color
        );
    }
}
