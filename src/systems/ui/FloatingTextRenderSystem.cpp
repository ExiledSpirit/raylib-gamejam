#include "FloatingTextRenderSystem.hpp"

#include "../../components/FloatingText.hpp"
#include "../../components/Transform2D.hpp"
#include "../../resources/FontResource.hpp"
#include "../../resources/GameCameraResource.hpp"
#include "../../utils/GameCameraUtils.hpp"

#include <ecs/resources/DisplayResource.hpp>

#include <raylib.h>
#include <algorithm>

void FloatingTextRenderSystem(World& world)
{
    auto view = world.registry.view<FloatingText, Transform2D>();
    auto font = world.GetResource<FontResource>();

    for(auto [entity, text, transform] : view.each())
    {
        (void)entity;

        float t = text.age / text.lifetime;
        float alpha = 1.0f - std::clamp(t, 0.0f, 1.0f);

        Color color = text.color;
        color.a = static_cast<unsigned char>(255.0f * alpha);

        // DrawTextEx(
        //     font.title,
        //     text.text.c_str(),
        //     Vector2{.x=transform.position.x,
        //     .y=transform.position.y},
        //     text.fontSize,
        //     0.f,
        //     color
        // );

    auto& camera = world.GetResource<GameCameraResource>();

    Camera2D camera2D = BuildRaylibCamera2D(
        camera,
        512,
        288
    );

    BeginMode2D(camera2D);
        DrawText(
            text.text.c_str(),
            static_cast<int>(transform.position.x),
            static_cast<int>(transform.position.y),
            text.fontSize,
            color
        );
    }
    EndMode2D();
}
