#include "GameStartupSystem.hpp"

#include "../../resources/asset/AssetManager.hpp"
#include "../../resources/GameStateResource.hpp"

#include "../../utils/AnimationHelper.hpp"
#include "../../utils/BackgroundHelper.hpp"
#include "../../utils/UiHelper.hpp"
#include "../../utils/AudioHelper.hpp"
#include "../../utils/LevelDiscovery.hpp"

#include "../../prefabs/PrefabRegistry.hpp"
#include "../../prefabs/RegisterPrefabs.hpp"

#include "../../config/InitializeCodelevel.hpp"

void GameStartupSystem(World& world)
{
    auto& assets =
        world.GetResource<AssetManager>();

    assets.LoadTexture("player", std::string(ASSETS_PATH) + "player.png");
    assets.LoadTexture("ball", std::string(ASSETS_PATH) + "ball.png");
    
    LoadAnimations(assets);
    LoadBackgrounds(assets);
    LoadUiAssets(assets);
    AudioHelper::InitializeAudioHelper();
    // AudioHelper::PlayMusic(AudioIds::SoundTrack_01, 1.f);`
    AudioHelper::PlaySoundtrack();

    auto& prefabs =
        world.GetResource<PrefabRegistry>();

    RegisterPrefabs(world, prefabs);

    // LoadLevelList(
    //     world,
    //     std::string(ASSETS_PATH) + "levels"
    // );

    // auto& gameState =
    //     world.GetResource<GameStateResource>();

    // gameState.screen = GameScreenOld::MainMenu;
    // gameState.previousScreen = GameScreenOld::MainMenu;
    // gameState.levelLoaded = false;
    // gameState.currentLevelPath.clear();

    InitializeCodeLevel(world);
}
