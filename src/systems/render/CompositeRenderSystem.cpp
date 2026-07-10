// #include "CompositeRenderSystem.hpp"

// #include <raylib.h>

// #include "../../resources/RenderTextureResources.hpp"
// // #include "../../resources/shader/CompositeShaderResources.hpp"
// #include "../../resources/GameStateResource.hpp"
// // static bool ShouldBypassLighting(GameScreen screen)
// // {
// //     return
// //         screen == GameScreen::MainMenu ||
// //         screen == GameScreen::LevelSelect ||
// //         screen == GameScreen::Options;
// // }
// void CompositeRenderSystem(World& world)
// {
//     auto& render =
//         world.GetResource<RenderTextureResources>();

//     auto& gameState =
//         world.GetResource<GameStateResource>();

//     // auto& compositeShader =
//     //     world.GetResource<CompositeShaderResources>();

// if(ShouldBypassLighting(gameState.screen))
// {
//     BeginTextureMode(render.postProcessA);
//     ClearBackground(BLACK);

//     DrawTexturePro(
//         render.worldRT.texture,
//         Rectangle{
//             0.f,
//             0.f,
//             static_cast<float>(render.worldRT.texture.width),
//             -static_cast<float>(render.worldRT.texture.height)
//         },
//         Rectangle{
//             0.f,
//             0.f,
//             static_cast<float>(render.postProcessA.texture.width),
//             static_cast<float>(render.postProcessA.texture.height)
//         },
//         Vector2{0.f, 0.f},
//         0.f,
//         WHITE
//     );

//     EndTextureMode();
//     return;
// }
//     BeginTextureMode(render.postProcessA);
//     ClearBackground(BLANK);

//     if(!gameState.levelLoaded)
//     {
//         EndTextureMode();
//         return;
//     }

//     BeginShaderMode(compositeShader.compositeShader);

//     SetShaderValueTexture(
//         compositeShader.compositeShader,
//         compositeShader.lightTextureLoc,
//         render.lightRT.texture
//     );

//     float ambientColor[3] = {0.4f, 0.4f, 0.4f};

//     SetShaderValue(
//         compositeShader.compositeShader,
//         compositeShader.ambientColorLoc,
//         ambientColor,
//         SHADER_UNIFORM_VEC3
//     );

//     DrawTexturePro(
//         render.worldRT.texture,
//         Rectangle{
//             0.f,
//             0.f,
//             static_cast<float>(render.worldRT.texture.width),
//             -static_cast<float>(render.worldRT.texture.height)
//         },
//         Rectangle{
//             0.f,
//             0.f,
//             static_cast<float>(render.postProcessA.texture.width),
//             static_cast<float>(render.postProcessA.texture.height)
//         },
//         Vector2{0.f, 0.f},
//         0.f,
//         WHITE
//     );

//     EndShaderMode();
//     EndTextureMode();
// }
