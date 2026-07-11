#pragma once

#include <raylib.h>

#include <vector>

struct CameraShakeBurst
{
    float intensity = 1.0f;

    float duration = 0.12f;
    float age = 0.0f;

    float frequency = 55.0f;

    float maxOffset = 5.0f;
    float maxRotation = 0.35f; // degrees
};

struct GameCameraResource
{
    Vector2 defaultTarget{256.0f, 144.0f};

    Vector2 target{256.0f, 144.0f};
    Vector2 position{256.0f, 144.0f};

    float zoom = 1.0f;
    float targetZoom = 1.0f;

    float speed = 12.0f;

    Vector2 shakeOffset{0.0f, 0.0f};
    float shakeRotation = 0.0f;
    float shakeTime = 0.0f;

    // Sustained shake: used by skill-check/charge states.
    // No age/duration. It is controlled by current gameplay state.
    float sustainedShakeIntensity = 0.0f;
    float targetSustainedShakeIntensity = 0.0f;

    float sustainedShakeFrequency = 48.0f;
    float sustainedShakeMaxOffset = 1.5f;
    float sustainedShakeMaxRotation = 0.08f;

    // Burst shakes: wall hits, impacts, explosions.
    std::vector<CameraShakeBurst> shakeBursts;

    float maxTotalShakeOffset = 10.0f;
    float maxTotalShakeRotation = 2.0f;
};
