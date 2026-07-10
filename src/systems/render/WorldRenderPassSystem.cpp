#include "WorldRenderPassSystem.hpp"

#include <raylib.h>

// #include "BackgroundRenderSystem.hpp"
#include "TileRenderSystem.hpp"
#include "SpriteRenderSystem.hpp"
// #include "DeathParticleRenderSystem.hpp"
// #include "../ui/MenuBackgroundRenderSystem.hpp"

// #include "../../resources/RenderTextureResources.hpp"
#include <ecs/resources/RenderTextureResources.hpp>
#include "../../resources/GameStateResource.hpp"

void WorldRenderPassSystem(World& world)
{
    auto& render =
        world.GetResource<RenderTextureResources>();

    auto& gameState =
        world.GetResource<GameStateResource>();

    // if(ShouldRenderMenuBackground(gameState.screen))
    // {
    //     MenuBackgroundRenderSystem(world);
    //     EndTextureMode();
    //     return;
    // }

    // if(!gameState.levelLoaded)
    // {
    //     EndTextureMode();
    //     return;
    // }

    // BackgroundRenderSystem(world);
    // TileRenderSystem(world);
    TileRenderSystem(world);
    SpriteRenderSystem(world);
    // DeathParticleRenderSystem(world);
}