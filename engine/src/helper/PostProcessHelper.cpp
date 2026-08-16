#include "PostProcessHelper.hpp"

#include "../ecs/resources/PostProcessResource.hpp"

#include <raylib.h>

#include <string>

static std::string BuildPostProcessShaderSource(const std::string& body)
{
#if defined(__EMSCRIPTEN__) || defined(PLATFORM_WEB)
    const char* header = R"(#version 100
precision mediump float;

#define VARYING varying
#define TEXTURE texture2D
#define FRAGCOLOR gl_FragColor
)";
#else
    const char* header = R"(#version 330

#define VARYING in
#define TEXTURE texture

out vec4 finalColor;
#define FRAGCOLOR finalColor
)";
#endif

    return std::string(header) + "\n" + body;
}

void LoadPostProcess(World& world)
{
    auto& post =
        world.GetResource<PostProcessResource>();

    if(post.loaded)
    {
        return;
    }

    std::string shaderPath = "assets/shaders/post_bloom_crt.fs";

    char* shaderBody =
        LoadFileText(shaderPath.c_str());

    if(shaderBody == nullptr)
    {
        TraceLog(
            LOG_WARNING,
            "POST PROCESS: Failed to read shader file: %s",
            shaderPath.c_str()
        );

        return;
    }

    std::string fragmentSource =
        BuildPostProcessShaderSource(shaderBody);

    UnloadFileText(shaderBody);

    post.shader =
        LoadShaderFromMemory(
            nullptr,
            fragmentSource.c_str()
        );

    if(post.shader.id == 0)
    {
        TraceLog(
            LOG_WARNING,
            "POST PROCESS: Failed to compile shader: %s",
            shaderPath.c_str()
        );

        return;
    }

    TraceLog(
        LOG_INFO,
        "POST PROCESS: Shader loaded successfully: %s",
        shaderPath.c_str()
    );

    post.loaded = true;
}

void UnloadPostProcess(World& world)
{
    auto& post =
        world.GetResource<PostProcessResource>();

    if(post.loaded && post.shader.id != 0)
    {
        UnloadShader(post.shader);
    }

    post = PostProcessResource{};
}