#include "InitializeResources.hpp"
#include "../resources/RunResource.hpp"
#include "../resources/IncomingBallResource.hpp"
#include "../resources/SkillCheckResource.hpp"
#include "../resources/StrikeZonesResource.hpp"
#include "../resources/GameScreenResource.hpp"
#include "../resources/GameStateResource.hpp"
#include "../resources/asset/AssetManager.hpp"
#include "../resources/DisplayResource.hpp"
#include "../resources/RenderTextureResources.hpp"
#include "../resources/TileDatabaseResource.hpp"
#include "../resources/TileMapResource.hpp"
#include "../resources/GameCameraResource.hpp"
#include "../resources/FontResource.hpp"
#include "../resources/HudAnimationResource.hpp"
#include "../prefabs/PrefabRegistry.hpp"
#include "../prefabs/RegisterPrefabs.hpp"
#include <physics/PhysicsWorldResource.hpp>
#include <box2d/box2d.h>
#include "../utils/CalculateViewport.hpp"

void InitializeResources(World& world) {
    LoadGameScreenResource(world);
    LoadGamePhysicsResource(world);
    LoadAssetManagerResource(world);
    LoadPrefabRegistry(world);
    LoadGameStateResources(world);
    InitializeGameMechanicsResources(world);
    LoadDisplayResources(world);
    LoadRenderTargetResources(world);
    LoadTileMapResources(world);
    LoadCameraResource(world);
    LoadFonts(world);
    LoadUiResource(world);
}

void LoadUiResource(World& world) {
    world.InsertResource<HudAnimationResource>();
}

void LoadFonts(World& world)
{
    auto& fonts = world.InsertResource<FontResource>();

    fonts.hud = LoadFontEx(
        ASSETS_PATH "fonts/balatro.otf",
        10,
        0,
        0
    );

    fonts.title = LoadFontEx(
        ASSETS_PATH "fonts/balatro.otf",
        32,
        0,
        0
    );

    SetTextureFilter(fonts.hud.texture, TEXTURE_FILTER_POINT);
    SetTextureFilter(fonts.title.texture, TEXTURE_FILTER_POINT);
}

void LoadCameraResource(World& world) {
    world.InsertResource<GameCameraResource>();
}

void LoadTileMapResources(World& world) {
    world.InsertResource<TileMapResource>();

    TileDatabaseResource database;

    database.definitions[TileId::Wall] =
    {
        .name = "Wall",
        .texture = LoadTexture((std::string(ASSETS_PATH) + "/tiles/wall.png").c_str()), // TODO: Replace LoadTexture for ResourceManager textureId
        .solid = true,
        .blocksLight = true
    };

    database.definitions[TileId::Empty] =
    {
        .name  = "Empty",
        .texture = {},
        .solid = false,
        .blocksLight = false
    };

    world.InsertResource<TileDatabaseResource>(database);
}

void LoadRenderTargetResources(World& world) {
    auto& displayResource = world.GetResource<DisplayResource>();
    
    int INTERNAL_WIDTH = displayResource.internalResolution.x;
    int INTERNAL_HEIGHT = displayResource.internalResolution.y;

    auto albedoRT = LoadRenderTexture(
        INTERNAL_WIDTH,
        INTERNAL_HEIGHT
    );

    auto normalRT = LoadRenderTexture(
        INTERNAL_WIDTH,
        INTERNAL_HEIGHT
    );

    RenderTextureResources renderTextureResources = {
        .worldRT = LoadRenderTexture(INTERNAL_WIDTH, INTERNAL_HEIGHT),
        .lightRT = LoadRenderTexture(INTERNAL_WIDTH, INTERNAL_HEIGHT),
        .debugRT = LoadRenderTexture(INTERNAL_WIDTH, INTERNAL_HEIGHT),
        .postProcessA = LoadRenderTexture(INTERNAL_WIDTH, INTERNAL_HEIGHT),
        .postProcessB = LoadRenderTexture(INTERNAL_WIDTH, INTERNAL_HEIGHT),
        .uiRT = LoadRenderTexture(INTERNAL_WIDTH, INTERNAL_HEIGHT)
    };

    SetTextureFilter(renderTextureResources.worldRT.texture, TEXTURE_FILTER_POINT);
    SetTextureFilter(renderTextureResources.lightRT.texture, TEXTURE_FILTER_POINT);
    SetTextureFilter(renderTextureResources.debugRT.texture, TEXTURE_FILTER_POINT);
    SetTextureFilter(renderTextureResources.postProcessA.texture, TEXTURE_FILTER_POINT);
    SetTextureFilter(renderTextureResources.uiRT.texture, TEXTURE_FILTER_POINT);

    world.InsertResource<RenderTextureResources>(renderTextureResources);
}

void LoadDisplayResources(World& world) {
    DisplayResource displayResource = DisplayResource();
    displayResource.internalResolution = {512, 288};
    displayResource.windowResolution = {(float)GetScreenWidth(), (float)GetScreenHeight()};

    CalculateViewport(displayResource);

    world.InsertResource<DisplayResource>(displayResource);
}

void InitializeGameMechanicsResources(World& world) {
    world.InsertResource<RunResource>();
    world.InsertResource<IncomingBallResource>();
    world.InsertResource<PlayerStrikeResource>();
    world.InsertResource<SkillCheckResource>();
}

void LoadGameStateResources(World& world) {
    world.InsertResource<GameStateResource>();
}

void LoadPrefabRegistry(World& world) {
    PrefabRegistry prefabRegistry = PrefabRegistry();

    RegisterPrefabs(world, prefabRegistry);
    world.InsertResource<PrefabRegistry>(prefabRegistry);
}

void LoadAssetManagerResource(World& world) {
    AssetManager assetManager = AssetManager();

    world.InsertResource<AssetManager>(assetManager);
}

void LoadGamePhysicsResource(World& world) {
    b2WorldDef worldDef = b2DefaultWorldDef();

    // Top-down golf-ish physics. No gravity.
    worldDef.gravity = b2Vec2{0.0f, 0.0f};

    auto& physics = world.InsertResource<PhysicsWorldResource>();
    physics.worldId = b2CreateWorld(&worldDef);
}

void LoadGameScreenResource(World& world) {
    auto gameScreenResource = GameScreenResource();
    world.InsertResource<GameScreenResource>(gameScreenResource);
}
