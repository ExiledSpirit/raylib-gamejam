#pragma once

#include <raylib.h>

struct RenderTextureResources
{
    RenderTexture2D scene{};
    RenderTexture2D scenePing{}; // For postprocessing shaders later
    RenderTexture2D scenePong{}; // for postprocessing shaders later

    RenderTexture2D ui{};
    RenderTexture2D composite{};

    Texture2D sceneOutput{};
    Texture2D finalOutput{};
};