#include "WorldRenderPassSystem.hpp"

#include "../../resources/GameCameraResource.hpp"
#include "../../utils/GameCameraUtils.hpp"

// include your render systems/helpers here
#include "TileRenderSystem.hpp"
#include "SpriteRenderSystem.hpp"

#include <raylib.h>

void WorldRenderPassSystem(World& world)
{
    auto& camera = world.GetResource<GameCameraResource>();

    Camera2D camera2D = BuildRaylibCamera2D(
        camera,
        512,
        288
    );

    BeginMode2D(camera2D);
    TileRenderSystem(world);

    SpriteRenderSystem(world);

    EndMode2D();
}