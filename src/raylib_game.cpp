#include <core/App.hpp>
#include <core/AppConfig.hpp>
#include "./config/ConfigureInput.hpp"
#include "./config/InitializeResources.hpp"

/** SYSTEMS */
#include <physics/PhysicsStepSystem.hpp>
#include "./systems/ui/MainMenuSystem.hpp"
#include "./systems/core/ShotEndSystem.hpp"
#include "./systems/core/GolfInputSystem.hpp"
#include "./systems/core/BallScoreSystem.hpp"
#include "./systems/core/BallPhysicsSyncSystem.hpp"
#include "./systems/render/GolfRenderSystem.hpp"
#include "./systems/ui/GolfUiSystem.hpp"

#include "./resources/LauncherResource.hpp"
#include "./resources/RunResource.hpp"


int main()
{
    AppConfig config = AppConfig();
    config.title = "NONAME";
    config.internalHeight = 180;
    config.internalWidth = 320;
    auto app = App(config);

    ConfigureInput(app.GetWorld());
    InitializeResources(app.GetWorld());
    // app.AddSystem(Stage::RenderUi, MainMenuUiSystem);
    // RegisterSystems(app.GetWorld());

    app.GetWorld().InsertResource<RunResource>();
    app.GetWorld().InsertResource<LauncherResource>();

    app.AddSystem(Stage::Update, GolfInputSystem);
    app.AddSystem(Stage::Update, PhysicsStepSystem);
    app.AddSystem(Stage::Update, BallPhysicsSyncSystem);
    app.AddSystem(Stage::Update, BallScoreSystem);
    app.AddSystem(Stage::Update, ShotEndSystem);

    app.AddSystem(Stage::RenderScene, GolfRenderSystem);
    app.AddSystem(Stage::RenderUi, GolfUiSystem);

    app.Run();

    return 1;
}
