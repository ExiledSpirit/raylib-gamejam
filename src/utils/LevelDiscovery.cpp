#include "LevelDiscovery.hpp"

#include <algorithm>
#include <filesystem>

#include "raylib.h"
#include "../resources/GameStateResource.hpp"

void LoadLevelList(
    World& world,
    const std::string& levelsDirectory)
{
    auto& gameState =
        world.GetResource<GameStateResource>();

    gameState.levels.clear();

    std::filesystem::path dir =
        levelsDirectory;

    if(!std::filesystem::exists(dir))
    {
        TraceLog(
            LOG_WARNING,
            "Levels directory does not exist: %s",
            levelsDirectory.c_str()
        );

        return;
    }

    for(const auto& entry : std::filesystem::directory_iterator(dir))
    {
        if(!entry.is_regular_file())
        {
            continue;
        }

        std::filesystem::path path =
            entry.path();

        if(path.extension() != ".json")
        {
            continue;
        }

        LevelEntry level;
        level.path = path.string();
        level.name = path.stem().string();

        gameState.levels.push_back(level);
    }

    std::sort(
        gameState.levels.begin(),
        gameState.levels.end(),
        [](const LevelEntry& a, const LevelEntry& b)
        {
            return a.name < b.name;
        }
    );

    if(gameState.levelSelectIndex >= static_cast<int>(gameState.levels.size()))
    {
        gameState.levelSelectIndex = 0;
    }

    TraceLog(
        LOG_INFO,
        "Loaded %d levels from %s",
        static_cast<int>(gameState.levels.size()),
        levelsDirectory.c_str()
    );
}