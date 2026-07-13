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
    assetManager.LoadTexture(
        "player_whiff_sheet",
        std::string(ASSETS_PATH) + "player_whiff_sheet.png"
    );
    assetManager.LoadTexture(
        "player_ready_sheet",
        std::string(ASSETS_PATH) + "player_ready_sheet.png"
    );
    assetManager.LoadTexture(
        "player_first_strike_sheet",
        std::string(ASSETS_PATH) + "player_first_strike_sheet.png"
    );
    assetManager.LoadTexture(
        "player_last_strike_sheet",
        std::string(ASSETS_PATH) + "player_last_strike_sheet.png"
    );
    
    assetManager.LoadTexture(
        "player_idle_right_sheet",
        std::string(ASSETS_PATH) + "player_idle_right_sheet.png"
    );
    assetManager.LoadTexture(
        "player_whiff_right_sheet",
        std::string(ASSETS_PATH) + "player_whiff_right_sheet.png"
    );
    assetManager.LoadTexture(
        "player_ready_right_sheet",
        std::string(ASSETS_PATH) + "player_ready_right_sheet.png"
    );
    assetManager.LoadTexture(
        "player_first_strike_right_sheet",
        std::string(ASSETS_PATH) + "player_first_strike_right_sheet.png"
    );
    assetManager.LoadTexture(
        "player_last_strike_right_sheet",
        std::string(ASSETS_PATH) + "player_last_strike_right_sheet.png"
    );

    assetManager.LoadAnimationFromSheet(
        AnimationIds::PlayerIdle,
        "player_idle_sheet",
        86, //86
        66, //66
        1, //1
        0.08f
    );
    
    assetManager.LoadAnimationFromSheet(
        AnimationIds::PlayerReady,
        "player_ready_sheet",
        86, //86
        66, //66
        1, //1
        0.08f
    );
    
    assetManager.LoadAnimationFromSheet(
        AnimationIds::PlayerFirstStrike,
        "player_first_strike_sheet",
        86, //86
        66, //66
        3, //1
        0.08f,
        false
    );
    
    assetManager.LoadAnimationFromSheet(
        AnimationIds::PlayerLastStrike,
        "player_last_strike_sheet",
        86, //86
        66, //66
        7, //1
        0.08f,
        false
    );
    
    assetManager.LoadAnimationFromSheet(
        AnimationIds::PlayerWhiff,
        "player_whiff_sheet",
        86, //86
        66, //66
        9, //1
        0.04f,
        false
    );
    
    assetManager.LoadAnimationFromSheet(
        AnimationIds::PlayerIdleRight,
        "player_idle_right_sheet",
        86, //86
        66, //66
        1, //1
        0.08f
    );
    
    assetManager.LoadAnimationFromSheet(
        AnimationIds::PlayerReadyRight,
        "player_ready_right_sheet",
        86, //86
        66, //66
        1, //1
        0.08f
    );
    
    assetManager.LoadAnimationFromSheet(
        AnimationIds::PlayerFirstStrikeRight,
        "player_first_strike_right_sheet",
        86, //86
        66, //66
        3, //1
        0.08f,
        false
    );
    
    assetManager.LoadAnimationFromSheet(
        AnimationIds::PlayerLastStrikeRight,
        "player_last_strike_right_sheet",
        86, //86
        66, //66
        7, //1
        0.08f,
        false
    );
    
    assetManager.LoadAnimationFromSheet(
        AnimationIds::PlayerWhiffRight,
        "player_whiff_right_sheet",
        86, //86
        66, //66
        9, //1
        0.04f,
        false
    );
}