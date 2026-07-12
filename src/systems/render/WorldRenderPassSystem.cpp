#include "WorldRenderPassSystem.hpp"

#include "../../resources/GameCameraResource.hpp"
#include "../../utils/GameCameraUtils.hpp"

// include your render systems/helpers here
#include "TileRenderSystem.hpp"
#include "SpriteRenderSystem.hpp"
#include "BackgroundRenderSystem.hpp"
#include "ArenaRenderSystem.hpp"

#include <raylib.h>

void WorldRenderPassSystem(World& world)
{
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