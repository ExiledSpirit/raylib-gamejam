#include <core/App.hpp>
#include <core/AppConfig.hpp>
#include "./config/ConfigureInput.hpp"
#include "./config/InitializeResources.hpp"

/** SYSTEMS */
#include <physics/PhysicsStepSystem.hpp>
#include "./systems/sfx/UpdateMusicSystem.hpp"
#include "./systems/startup/GameStartupSystem.hpp"
#include "./systems/core/MainMenuIntroSystem.hpp"
#include "./systems/core/ShotEndSystem.hpp"
#include "./systems/core/BallScoreSystem.hpp"
#include "./systems/core/BallPhysicsSyncSystem.hpp"

#include "./systems/core/MainMenuInputSystem.hpp"
#include "./systems/core/StartDropBallSystem.hpp"
#include "./systems/core/FallingBallStrikeSystem.hpp"
#include "./systems/core/FirstStrikeAnimationSystem.hpp"
#include "./systems/core/SkillCheckSystem.hpp"
#include "./systems/core/LaunchSkillCheckResolverSystem.hpp"
#include "./systems/core/ShopSkillCheckResolverSystem.hpp"
#include "./systems/core/LastStrikeAnimationSystem.hpp"
#include "./systems/core/BallWallHitSystem.hpp"
#include "./systems/core/BallLowSpeedDampingSystem.hpp"
#include "./systems/core/RunEndInputSystem.hpp"

#include "./systems/animation/PlayerAnimationSystem.hpp"
#include "./systems/animation/AnimationSystem.hpp"

#include "./systems/render/PlayingSceneRenderSystem.hpp"
#include "./systems/render/ShopSceneRenderSystem.hpp"
#include "./systems/render/MainMenuSceneRenderSystem.hpp"

#include "./systems/ui/HudAnimationSystem.hpp"
#include "./systems/ui/HudPayoutSystem.hpp"
#include "./systems/ui/RewardPopupSystem.hpp"
#include "./systems/ui/FloatingTextSystem.hpp"
#include "./systems/ui/PlayingUiSystem.hpp"
#include "./systems/ui/MainMenuUiSystem.hpp"
#include "./systems/ui/ScreenTransitionSystem.hpp"
#include "./systems/ui/ScreenTransitionRenderSystem.hpp"
#include "./systems/ui/ShopUiSystem.hpp"
#include "./systems/ui/RunEndAnimationSystem.hpp"

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
    config.title = "TOY OUT";
    config.internalHeight = 360;
    config.internalWidth = 640;
    config.windowHeight = 720;
    config.windowWidth = 1280;
    auto app = App(config);

    ConfigureInput(app.GetWorld());
    InitializeResources(app.GetWorld());

    app.GetWorld().InsertResource<RunResource>();
    app.GetWorld().InsertResource<LauncherResource>();

    app.AddStartupSystem(GameStartupSystem);

    app.AddSystem(Stage::Update, MainMenuIntroSystem);
    app.AddSystem(Stage::Update, MainMenuInputSystem);
    app.AddSystem(Stage::Update, StartDropBallSystem);
    app.AddSystem(Stage::Update, FallingBallStrikeSystem);
    app.AddSystem(Stage::Update, FirstStrikeAnimationSystem);
    app.AddSystem(Stage::Update, SkillCheckSystem);
    app.AddSystem(Stage::Update, LaunchSkillCheckResolverSystem);
    app.AddSystem(Stage::Update, ShopSkillCheckResolverSystem);
    app.AddSystem(Stage::Update, LastStrikeAnimationSystem);
    app.AddSystem(Stage::Update, RunEndInputSystem);

    app.AddSystem(Stage::Update, PlayerAnimationSystem);
    app.AddSystem(Stage::Update, AnimationSystem);

    app.AddSystem(Stage::Update, UpdateMusicSystem);

    app.AddSystem(Stage::Update, PhysicsStepSystem);
    app.AddSystem(Stage::Update, BallPhysicsSyncSystem);
    app.AddSystem(Stage::Update, BallScoreSystem);
    app.AddSystem(Stage::Update, BallWallHitSystem);
    app.AddSystem(Stage::Update, BallLowSpeedDampingSystem);
    app.AddSystem(Stage::Update, FloatingTextSystem);
    app.AddSystem(Stage::Update, HudAnimationSystem);
    app.AddSystem(Stage::Update, HudPayoutSystem);
    app.AddSystem(Stage::Update, RewardPopupSystem);
    app.AddSystem(Stage::Update, RunEndAnimationSystem);
    app.AddSystem(Stage::Update, ShotEndSystem);

    app.AddSystem(Stage::Update, CameraTargetSystem);
    app.AddSystem(Stage::Update, CameraUpdateSystem);
    app.AddSystem(Stage::Update, ScreenTransitionSystem);

    // MENU
    app.AddSystem(Stage::RenderScene, MainMenuSceneRenderSystem);
    app.AddSystem(Stage::RenderUi, MainMenuUiSystem);

    // PLAYING
    app.AddSystem(Stage::RenderScene, PlayingSceneRenderSystem);
    app.AddSystem(Stage::RenderUi, PlayingUiSystem);

    // SHOP
    app.AddSystem(Stage::RenderScene, ShopSceneRenderSystem);
    app.AddSystem(Stage::RenderUi, ShopUiSystem);

    app.AddSystem(Stage::RenderUi, ScreenTransitionRenderSystem);
    app.Run();

    return 1;
}
