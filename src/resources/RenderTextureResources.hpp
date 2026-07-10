#pragma once

#include <raylib.h>

struct RenderTextureResources {
    // RenderTexture2D albedoRT;
    // RenderTexture2D normalRT;
    RenderTexture2D worldRT;
    RenderTexture2D lightRT;
    RenderTexture2D debugRT;
    RenderTexture2D postProcessA;
    RenderTexture2D postProcessB;

    RenderTexture2D uiRT;
};
