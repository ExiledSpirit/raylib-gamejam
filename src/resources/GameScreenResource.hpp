#pragma once

enum class GameScreen
{
    MainMenu,
    Playing,
    Shop
};

struct GameScreenResource
{
    GameScreen current = GameScreen::MainMenu;
    GameScreen target = GameScreen::MainMenu;
};
