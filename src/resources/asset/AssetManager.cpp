#include "AssetManager.hpp"
#include <stdexcept>

Texture2D& AssetManager::LoadTexture(
    const std::string& id,
    const std::string& path)
{
    auto it =
        textures.find(id);

    if(it != textures.end())
    {
        return it->second;
    }

    textures[id] =
        ::LoadTexture(path.c_str());

    SetTextureFilter(textures[id], TEXTURE_FILTER_POINT);
    SetTextureWrap(textures[id], TEXTURE_WRAP_CLAMP);

    return textures[id];
}

Texture2D& AssetManager::GetTexture(const std::string& id)
{
    auto it =
        textures.find(id);

    if(it == textures.end())
    {
        TraceLog(
            LOG_ERROR,
            "Missing texture id: '%s'",
            id.c_str()
        );

        throw std::out_of_range(
            "Missing texture id: " + id
        );
    }

    return it->second;
}

Shader& AssetManager::LoadShader(
    const std::string& id,
    const std::string& vertexPath,
    const std::string& fragmentPath)
{
    auto it =
        shaders.find(id);

    if(it != shaders.end())
    {
        return it->second;
    }

    shaders[id] =
        ::LoadShader(
            vertexPath.c_str(),
            fragmentPath.c_str());

    return shaders[id];
}

AssetManager::~AssetManager()
{
    UnloadAll();
}

void AssetManager::UnloadAll()
{
    for(auto& [id, texture]
        : textures)
    {
        ::UnloadTexture(texture);
    }

    textures.clear();

    for(auto& [id, shader]
        : shaders)
    {
        ::UnloadShader(shader);
    }

    shaders.clear();
}

AnimationClip& AssetManager::LoadAnimationFromSheet(
    const std::string& id,
    const std::string& textureId,
    int frameWidth,
    int frameHeight,
    int frameCount,
    float frameDuration,
    bool loop)
{
    TraceLog(
        LOG_WARNING,
        "Loading animation '%s' from texture '%s'",
        id.c_str(),
        textureId.c_str()
    );

    if(textures.find(textureId) == textures.end())
    {
        TraceLog(
            LOG_ERROR,
            "Missing texture while loading animation. animationId='%s', textureId='%s'",
            id.c_str(),
            textureId.c_str()
        );

        throw std::runtime_error(
            "Missing texture while loading animation: " + id +
            " uses texture: " + textureId
        );
    }

    AnimationClip clip;

    clip.texture =
        &textures.at(textureId);

    clip.frameDuration =
        frameDuration;

    clip.loop =
        loop;

    for(int i = 0; i < frameCount; i++)
    {
        clip.frames.push_back(
        {
            static_cast<float>(i * frameWidth),
            0.f,
            static_cast<float>(frameWidth),
            static_cast<float>(frameHeight)
        });
    }

    animations[id] =
        std::move(clip);

    return animations.at(id);
}

Shader& AssetManager::GetShader(
    const std::string& id)
{
    return shaders.at(id);
}

AnimationClip& AssetManager::GetAnimation(const std::string& id)
{
    return animations.at(id);
}
