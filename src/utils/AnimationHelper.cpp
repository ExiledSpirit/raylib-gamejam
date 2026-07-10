#include "AnimationHelper.hpp"
#include "../const/AnimationIds.hpp"

void PlayAnimation(
    AnimationPlayer& player,
    AnimationClip* clip
) {
    if(player.currentClip == clip)
    {
        return;
    }

    player.currentClip = clip;
    player.currentFrame = 0;
    player.timer = 0.f;
}

void LoadAnimations(
    AssetManager& assetManager)
{
    assetManager.LoadTexture(
        "player_idle_sheet",
        std::string(ASSETS_PATH) + "player_idle_sheet.png"
    );
    // assetManager.LoadTexture(
    //     "player_striking_sheet",
    //     "assets/player/player_striking_sheet.png"
    // );
    // assetManager.LoadTexture(
    //     "player_striked_sheet",
    //     "assets/player/player_striked_sheet.png"
    // );

    assetManager.LoadAnimationFromSheet(
        AnimationIds::PlayerIdle,
        "player_idle_sheet",
        16,
        32,
        4,
        0.08f
    );
    // assetManager.LoadAnimationFromSheet(
    //     AnimationIds::PlayerIdle,
    //     "player_striking_sheet",
    //     8,
    //     8,
    //     18,
    //     0.08f
    // );
    // assetManager.LoadAnimationFromSheet(
    //     AnimationIds::PlayerIdle,
    //     "player_striked_sheet",
    //     8,
    //     8,
    //     18,
    //     0.08f
    // );
    
}