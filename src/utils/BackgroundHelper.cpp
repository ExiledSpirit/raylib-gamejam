#include "BackgroundHelper.hpp"
#include "../const/BackgroundIds.hpp"

void LoadBackgrounds(
    AssetManager& assetManager
) {
    assetManager.LoadTexture(
        BackgroundIds::Background_01,
        "assets/backgrounds/background_01.png"
    );
}