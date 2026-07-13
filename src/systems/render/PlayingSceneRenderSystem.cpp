#include "PlayingSceneRenderSystem.hpp"

#include "../../resources/GameScreenResource.hpp"
#include "../../resources/GameCameraResource.hpp"
#include "../../utils/GameCameraUtils.hpp"

#include "TileRenderSystem.hpp"
#include "SpriteRenderSystem.hpp"
#include "BackgroundRenderSystem.hpp"
#include "ArenaRenderSystem.hpp"
#include <raylib.h>

void PlayingSceneRenderSystem(World& world)
{
    auto& screen = world.GetResource<GameScreenResource>();

    if(screen.current != GameScreen::Playing)
    {
        return;
    }

    auto& camera = world.GetResource<GameCameraResource>();

    Camera2D camera2D = BuildRaylibCamera2D(
        camera,
        640,
        360
    );

    BeginMode2D(camera2D);

    BackgroundRenderSystem(world);
    ArenaRenderSystem(world);
    // TileRenderSystem(world);
    SpriteRenderSystem(world);

    EndMode2D();
}
