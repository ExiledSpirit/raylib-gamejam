#pragma once

#include "../resources/GameCameraResource.hpp"

inline void AddCameraShake(
    GameCameraResource& camera,
    float intensity,
    float duration,
    float maxOffset,
    float maxRotation,
    float frequency
)
{
    CameraShakeBurst burst{};
    burst.intensity = intensity;
    burst.duration = duration;
    burst.maxOffset = maxOffset;
    burst.maxRotation = maxRotation;
    burst.frequency = frequency;

    camera.shakeBursts.push_back(burst);
}
