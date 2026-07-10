#pragma once

#include <raylib.h>

#include <string>
#include <unordered_map>
#include "AnimationClip.hpp"

class AssetManager
{
public:

    ~AssetManager();

    Texture2D& LoadTexture(
        const std::string& id,
        const std::string& path);

    Texture2D& GetTexture(
        const std::string& id);

    Shader& LoadShader(
        const std::string& id,
        const std::string& vertexPath,
        const std::string& fragmentPath);

    Shader& GetShader(
        const std::string& id);

    AnimationClip& LoadAnimation(
        const std::string& id,
        const std::vector<std::string>& textureIds,
        float frameDuration);
    
    AnimationClip& LoadAnimationFromSheet(
        const std::string& id,
        const std::string& textureId,
        int frameWidth,
        int frameHeight,
        int frameCount,
        float frameDuration,
        bool loop = true);

    AnimationClip& GetAnimation(const std::string& id);

    void UnloadAll();

private:

    std::unordered_map<
        std::string,
        Texture2D> textures;

    std::unordered_map<
        std::string,
        Shader> shaders;
        private:

    std::unordered_map<
        std::string,
        AnimationClip> animations;
};