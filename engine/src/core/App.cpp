#include "App.hpp"

#include <algorithm>

#include "../ecs/resources/TimeResource.hpp"

#include "../input/InputBindings.hpp"
#include "../input/InputResource.hpp"
#include "../input/InputSystem.hpp"

#include "../ui/UiContext.hpp"

#include "../ecs/resources/DisplayResource.hpp"
#include "../ecs/resources/RenderTextureResources.hpp"
#include "../rendering/RenderPipelineSystems.hpp"

#include <raylib.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

static void InitializeCoreResources(
    World& world,
    const AppConfig& config
)
{
    world.InsertResource<TimeResource>();

    world.InsertResource<InputResource>();
    world.InsertResource<InputBindings>();

    world.InsertResource<UiContext>();

    world.InsertResource<DisplayResource>();
    world.InsertResource<RenderTextureResources>();

    auto& display =
        world.GetResource<DisplayResource>();

    display.internalWidth = config.internalWidth;
    display.internalHeight = config.internalHeight;

    display.windowWidth = config.windowWidth;
    display.windowHeight = config.windowHeight;

    auto& renderTextures =
        world.GetResource<RenderTextureResources>();

    renderTextures.scene = LoadRenderTexture(
        display.internalWidth,
        display.internalHeight
    );

    renderTextures.ui = LoadRenderTexture(
        display.internalWidth,
        display.internalHeight
    );

    renderTextures.composite = LoadRenderTexture(
        display.internalWidth,
        display.internalHeight
    );

    SetTextureFilter(
        renderTextures.scene.texture,
        TEXTURE_FILTER_POINT
    );

    SetTextureFilter(
        renderTextures.ui.texture,
        TEXTURE_FILTER_POINT
    );

    SetTextureFilter(
        renderTextures.composite.texture,
        TEXTURE_FILTER_POINT
    );

    renderTextures.sceneOutput =
        renderTextures.scene.texture;

    renderTextures.finalOutput =
        renderTextures.composite.texture;
}

static void RegisterEngineSystems(Scheduler& scheduler)
{
    scheduler.AddSystem(
        Stage::PreUpdate,
        InputSystem
    );

    scheduler.AddSystem(
        Stage::BeginScene,
        BeginSceneRenderSystem
    );

    scheduler.AddSystem(
        Stage::ScenePostProcess,
        ScenePostProcessSystem
    );

    scheduler.AddSystem(
        Stage::BeginUi,
        BeginUiRenderSystem
    );

    scheduler.AddSystem(
        Stage::Composite,
        CompositeRenderSystem
    );

    scheduler.AddSystem(
        Stage::Present,
        PresentRenderSystem
    );

    scheduler.AddSystem(
        Stage::Shutdown,
        ShutdownRenderSystem
    );
}

App::App(const AppConfig& config)
{
    InitWindow(
        config.windowWidth,
        config.windowHeight,
        config.title
    );

    SetExitKey(config.exitKey);
    SetTargetFPS(config.targetFps);

    InitializeCoreResources(
        world,
        config
    );

    RegisterEngineSystems(
        scheduler
    );
}

void App::Frame()
{
    auto& time =
        world.GetResource<TimeResource>();

    float rawDeltaTime =
        GetFrameTime();

    constexpr float maxDeltaTime =
        1.0f / 30.0f;

    time.deltaTime =
        std::min(rawDeltaTime, maxDeltaTime);

    scheduler.RunStage(
        Stage::PreUpdate,
        world
    );

    scheduler.RunStage(
        Stage::Update,
        world
    );

    scheduler.RunStage(
        Stage::PostUpdate,
        world
    );

    scheduler.RunStage(
        Stage::BeginScene,
        world
    );

    scheduler.RunStage(
        Stage::RenderScene,
        world
    );

    scheduler.RunStage(
        Stage::ScenePostProcess,
        world
    );

    scheduler.RunStage(
        Stage::BeginUi,
        world
    );

    scheduler.RunStage(
        Stage::RenderUi,
        world
    );

    scheduler.RunStage(
        Stage::Composite,
        world
    );

    scheduler.RunStage(
        Stage::Present,
        world
    );
}

void App::Run()
{
    scheduler.RunStage(
        Stage::Startup,
        world
    );

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(
        [](void* userData)
        {
            App* app =
                static_cast<App*>(userData);

            app->Frame();
        },
        this,
        0,
        1
    );
#else
    while(!WindowShouldClose())
    {
        Frame();
    }

    scheduler.RunStage(
        Stage::Shutdown,
        world
    );

    CloseWindow();
#endif
}

void App::AddStartupSystem(SystemFn system)
{
    scheduler.AddSystem(
        Stage::Startup,
        system
    );
}

void App::AddSystem(Stage stage, SystemFn system)
{
    scheduler.AddSystem(
        stage,
        system
    );
}

World& App::GetWorld()
{
    return world;
}