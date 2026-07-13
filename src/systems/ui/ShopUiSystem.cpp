#include "ShopUiSystem.hpp"

#include <raylib.h>
#include "../../utils/GameCameraUtils.hpp"
#include "../../resources/GameScreenResource.hpp"
#include "SkillCheckUiSystem.hpp"
#include "SkillCheckUiSystem.hpp"
#include "ShopInfoRenderSystem.hpp"
#include "FloatingTextRenderSystem.hpp"
// #include "ShopGoldHudSystem.hpp"

void ShopUiSystem(World& world)
{
    auto& screen = world.GetResource<GameScreenResource>();

    if(screen.current != GameScreen::Shop)
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
    SkillCheckUiSystem(world);
    ShopInfoRenderSystem(world);
    FloatingTextRenderSystem(world);
    EndMode2D();
    // ShopGoldHudSystem(world);
}
