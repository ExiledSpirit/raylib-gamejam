#include "ShopSceneRenderSystem.hpp"

#include "../../resources/GameScreenResource.hpp"

#include <raylib.h>

void ShopSceneRenderSystem(World& world)
{
    auto& screen = world.GetResource<GameScreenResource>();

    if(screen.current != GameScreen::Shop)
    {
        return;
    }

    ClearBackground(Color{12, 10, 18, 255});

    // Later:
    // ShopShaderBackgroundSystem(world);
    // ShopDecorationRenderSystem(world);
}
