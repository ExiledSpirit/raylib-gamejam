#pragma once

enum class GameScreen
{
    MainMenu,
    Playing,
    Shop
};

struct GameScreenResource
{
    GameScreen current = GameScreen::Playing;
    GameScreen target = GameScreen::Playing;
};
