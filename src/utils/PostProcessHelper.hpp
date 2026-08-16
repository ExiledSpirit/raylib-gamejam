#pragma once

#include <core/World.hpp>
#include "../resources/PostProcessResource.hpp"

#include <raylib.h>

#include <string>

static inline void LoadPostProcess(World& world)
{
    auto& post =
        world.GetResource<PostProcessResource>();

    if(post.loaded)
    {
        return;
    }

    std::string path =
        std::string(ASSETS_PATH) + "/shaders/post_bloom_crt.fs";

    post.shader =
        LoadShader(nullptr, path.c_str());

    if(post.shader.id == 0)
    {
        TraceLog(
            LOG_WARNING,
            "POST PROCESS: Failed to load shader: %s",
            path.c_str()
        );

        return;
    }
    post.loaded = true;
}

static inline void UnloadPostProcess(World& world)
{
    auto& post =
        world.GetResource<PostProcessResource>();

    if(post.loaded && post.shader.id != 0)
    {
        UnloadShader(post.shader);
    }

    post = PostProcessResource{};
}