#include <core/App.hpp>
#include <core/AppConfig.hpp>
#include "./config/ConfigureInput.hpp"
#include "./config/InitializeResources.hpp"

/** SYSTEMS */
#include <physics/PhysicsStepSystem.hpp>
#include "./systems/sfx/UpdateMusicSystem.hpp"
#include "./systems/startup/GameStartupSystem.hpp"
#include "./systems/ui/MainMenuSystem.hpp"
#include "./systems/core/ShotEndSystem.hpp"
#include "./systems/core/GolfInputSystem.hpp"
#include "./systems/core/BallScoreSystem.hpp"
#include "./systems/core/BallPhysicsSyncSystem.hpp"

#include "./systems/core/StartDropBallSystem.hpp"
#include "./systems/core/FallingBallStrikeSystem.hpp"
#include "./systems/core/FirstStrikeAnimationSystem.hpp"
#include "./systems/core/SkillCheckSystem.hpp"
#include "./systems/core/LastStrikeAnimationSystem.hpp"
#include "./systems/core/BallWallHitSystem.hpp"

#include "./systems/animation/PlayerAnimationSystem.hpp"
#include "./systems/animation/AnimationSystem.hpp"

#include "./systems/render/WorldRenderPassSystem.hpp"
#include "./systems/ui/GolfUiSystem.hpp"
#include "./systems/ui/SkillCheckUiSystem.hpp"
#include "./systems/ui/FloatingTextSystem.hpp"
#include "./systems/ui/FloatingTextRenderSystem.hpp"

#include "./systems/camera/CameraTargetSystem.hpp"
#include "./systems/camera/CameraUpdateSystem.hpp"

#include "./systems/debugs/DebugUiSystem.hpp"
#include "./systems/debugs/DebugIncomingBallRenderSystem.hpp"

#include "./resources/LauncherResource.hpp"
#include "./resources/RunResource.hpp"

int main()
{
    ChangeDirectory(GetApplicationDirectory());
    AppConfig config = AppConfig();
    config.title = "MY BASEBALL BAT";
    config.internalHeight = 288;
    config.internalWidth = 512;
    config.windowHeight = 864;
    config.windowWidth = 1536;
    auto app = App(config);

    ConfigureInput(app.GetWorld());
    InitializeResources(app.GetWorld());

    app.GetWorld().InsertResource<RunResource>();
    app.GetWorld().InsertResource<LauncherResource>();

    app.AddStartupSystem(GameStartupSystem);

    app.AddSystem(Stage::Update, StartDropBallSystem);
    app.AddSystem(Stage::Update, FallingBallStrikeSystem);
    app.AddSystem(Stage::Update, FirstStrikeAnimationSystem);
    app.AddSystem(Stage::Update, SkillCheckSystem);
    app.AddSystem(Stage::Update, LastStrikeAnimationSystem);

    app.AddSystem(Stage::Update, PlayerAnimationSystem);
    app.AddSystem(Stage::Update, AnimationSystem);

    app.AddSystem(Stage::Update, UpdateMusicSystem);

    app.AddSystem(Stage::Update, PhysicsStepSystem);
    app.AddSystem(Stage::Update, BallPhysicsSyncSystem);
    app.AddSystem(Stage::Update, BallScoreSystem);
    app.AddSystem(Stage::Update, BallWallHitSystem);
    app.AddSystem(Stage::Update, FloatingTextSystem);
    app.AddSystem(Stage::Update, ShotEndSystem);

    // app.AddSystem(Stage::Update, PhysicsStepSystem);
    // app.AddSystem(Stage::Update, BallPhysicsSyncSystem);
    // app.AddSystem(Stage::Update, BallScoreSystem);
    // app.AddSystem(Stage::Update, ShotEndSystem);

    app.AddSystem(Stage::Update, CameraTargetSystem);
    app.AddSystem(Stage::Update, CameraUpdateSystem);

    app.AddSystem(Stage::RenderScene, WorldRenderPassSystem);
    // app.AddSystem(Stage::RenderScene, DebugIncomingBallRenderSystem); // Debug

    app.AddSystem(Stage::RenderUi, FloatingTextRenderSystem);
    app.AddSystem(Stage::RenderUi, SkillCheckUiSystem);
    app.AddSystem(Stage::RenderUi, DebugUiSystem);

    app.Run();

    return 1;
}
