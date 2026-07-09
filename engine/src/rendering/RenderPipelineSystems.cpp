#include "RenderPipelineSystems.hpp"

#include "../ecs/resources/DisplayResource.hpp"
#include "../ecs/resources/RenderTextureResources.hpp"

#include <algorithm>
#include <cmath>

#include <raylib.h>

static void UpdateDisplayResource(World& world)
{
    auto& display =
        world.GetResource<DisplayResource>();

    display.windowWidth = GetScreenWidth();
    display.windowHeight = GetScreenHeight();

    float scaleX =
        static_cast<float>(display.windowWidth) /
        static_cast<float>(display.internalWidth);

    float scaleY =
        static_cast<float>(display.windowHeight) /
        static_cast<float>(display.internalHeight);

    display.scale =
        std::floor(std::min(scaleX, scaleY));

    if(display.scale < 1.0f)
    {
        display.scale = 1.0f;
    }

    display.viewportSize = Vector2{
        static_cast<float>(display.internalWidth) * display.scale,
        static_cast<float>(display.internalHeight) * display.scale
    };

    display.viewportOffset = Vector2{
        (static_cast<float>(display.windowWidth) - display.viewportSize.x) * 0.5f,
        (static_cast<float>(display.windowHeight) - display.viewportSize.y) * 0.5f
    };
}

static void DrawTextureToInternalTarget(Texture2D texture, int width, int height)
{
    DrawTexturePro(
        texture,
        Rectangle{
            0.0f,
            0.0f,
            static_cast<float>(texture.width),
            -static_cast<float>(texture.height)
        },
        Rectangle{
            0.0f,
            0.0f,
            static_cast<float>(width),
            static_cast<float>(height)
        },
        Vector2{0.0f, 0.0f},
        0.0f,
        WHITE
    );
}

void BeginSceneRenderSystem(World& world)
{
    auto& rt =
        world.GetResource<RenderTextureResources>();

    BeginTextureMode(rt.scene);
    ClearBackground(BLACK);
}

void ScenePostProcessSystem(World& world)
{
    auto& rt =
        world.GetResource<RenderTextureResources>();

    EndTextureMode();

    // No shaders yet.
    // Later: rt.scene.texture -> scene post pipeline -> rt.sceneOutput.
    rt.sceneOutput = rt.scene.texture;
}

void BeginUiRenderSystem(World& world)
{
    auto& rt =
        world.GetResource<RenderTextureResources>();

    BeginTextureMode(rt.ui);
    ClearBackground(BLANK);
}

void CompositeRenderSystem(World& world)
{
    auto& rt =
        world.GetResource<RenderTextureResources>();

    auto& display =
        world.GetResource<DisplayResource>();

    EndTextureMode();

    BeginTextureMode(rt.composite);
    ClearBackground(BLANK);

    DrawTextureToInternalTarget(
        rt.sceneOutput,
        display.internalWidth,
        display.internalHeight
    );

    DrawTextureToInternalTarget(
        rt.ui.texture,
        display.internalWidth,
        display.internalHeight
    );

    EndTextureMode();

    rt.finalOutput = rt.composite.texture;
}

void PresentRenderSystem(World& world)
{
    auto& display =
        world.GetResource<DisplayResource>();

    auto& rt =
        world.GetResource<RenderTextureResources>();

    UpdateDisplayResource(world);

    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexturePro(
        rt.finalOutput,
        Rectangle{
            0.0f,
            0.0f,
            static_cast<float>(rt.finalOutput.width),
            -static_cast<float>(rt.finalOutput.height)
        },
        Rectangle{
            display.viewportOffset.x,
            display.viewportOffset.y,
            display.viewportSize.x,
            display.viewportSize.y
        },
        Vector2{0.0f, 0.0f},
        0.0f,
        WHITE
    );

    EndDrawing();
}

void ShutdownRenderSystem(World& world)
{
    auto& rt =
        world.GetResource<RenderTextureResources>();

    UnloadRenderTexture(rt.scene);
    UnloadRenderTexture(rt.ui);
    UnloadRenderTexture(rt.composite);
}