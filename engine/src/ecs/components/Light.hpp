#pragma once

#include <raylib.h>

struct LightComponent {
    Color color;
    float radius;
    float intensity;

    float flickerAmount; // Broken lamp, etc
    float flickerSpeed;

    float noiseAmount; // Fire/ Torch
    float noiseScale;

    bool castsShadow; // Casts shadow agains solid bodies
};
