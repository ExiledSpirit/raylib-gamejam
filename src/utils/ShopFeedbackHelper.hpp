#pragma once

#include <core/World.hpp>
#include "AudioHelper.hpp"
#include "../const/AudioIds.hpp"
#include "../factories/FloatingTextFactory.hpp"
#include "CameraShakeUtils.hpp"

#include <raylib.h>

inline static const char* GetRandomDeniedText()
{
    int index =
        GetRandomValue(0, 2);

    switch(index)
    {
        case 0:
            return "u broke?";

        case 1:
            return "u have no money...";

        case 2:
        default:
            return "stop it";
    }
}

inline void TriggerShopDeniedFeedback(
    World& world,
    Vector2 position
)
{
    auto& camera = world.GetResource<GameCameraResource>();
    AddCameraShake(
        camera,
        0.20f,  // intensity
        0.24f,  // duration
        10.0f,   // max offset
        0.25f,  // max rotation
        10.0f   // frequency
    );
    CreateFloatingText(
        world,
        GetRandomDeniedText(),
        position,
        WHITE,
        1.5f,
        20.f
    );
    AudioHelper::PlaySfx(AudioIds::SkillCheckMiss);
}