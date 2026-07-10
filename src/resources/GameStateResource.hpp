#pragma once

#include <string>
#include <vector>

enum class GameScreenOld
{
    MainMenu,
    Options,
    Playing,
    Paused,
    LevelFailed,
    ScoreCalculation
};

struct LevelEntry
{
    std::string name;
    std::string path;
};

struct GameStateResource
{
    GameScreenOld screen = GameScreenOld::MainMenu;
    GameScreenOld previousScreen = GameScreenOld::MainMenu;

    std::vector<LevelEntry> levels;

    int mainMenuIndex = 0;
    int pauseMenuIndex = 0;
    int optionsIndex = 0;
    int levelSelectIndex = 0;

    bool levelLoaded = false;
    std::string currentLevelPath;
};
