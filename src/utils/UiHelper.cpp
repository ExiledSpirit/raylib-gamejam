#include "UiHelper.hpp"
#include "../const/UiAssetsIds.hpp"

void LoadUiAssets(AssetManager& assetManager) {
    assetManager.LoadTexture(
        UiAssetIds::DeathCounter,
        "assets/ui/ui_death_counter.png"
    );
    assetManager.LoadTexture(
        UiAssetIds::PowerCounter,
        "assets/ui/ui_power_counter.png"
    );
    assetManager.LoadTexture(
        UiAssetIds::NormalKey,
        "assets/ui/ui_normal_key.png"
    );
    assetManager.LoadTexture(
        UiAssetIds::SpaceKey,
        "assets/ui/ui_space_key.png"
    );
    assetManager.LoadTexture(
        UiAssetIds::TimerPlate,
        "assets/ui/ui_timer_plate.png"
    );
    assetManager.LoadTexture(
        UiAssetIds::Clock,
        "assets/ui/ui_clock.png"
    );
    assetManager.LoadTexture(
        UiAssetIds::Score,
        "assets/ui/ui_score.png"
    );
    assetManager.LoadTexture(
        UiAssetIds::MenuPlate,
        "assets/ui/ui_menu_plate.png"
    );
    assetManager.LoadTexture(
        UiAssetIds::MainTitle,
        "assets/ui/main_title.png"
    );
}
