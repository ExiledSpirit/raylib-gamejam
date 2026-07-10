#pragma once

#include "../components/animation/AnimationPlayer.hpp"
#include "../resources/asset/AssetManager.hpp"

void PlayAnimation(
    AnimationPlayer& player,
    AnimationClip* clip);

void LoadAnimations(
    AssetManager& assetManager
);