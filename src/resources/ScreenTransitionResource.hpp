#pragma once

#include "GameScreenResource.hpp"

#include <raylib.h>
#include <vector>

enum class ScreenTransitionPhase
{
    None,
    Covering,
    Covered,
    Uncovering
};

enum class ScreenTransitionAction
{
    None,
    StartPlaying,
    EnterShop,
    ExitShopToPlaying,
    ReturnToMenu
};

struct TransitionShape
{
    Vector2 position{};
    float startSize = 8.0f;
    float endSize = 900.0f;
    float rotation = 0.0f;
    int sides = 4;
    Color color = BLACK;
};

struct ScreenTransitionResource
{
    bool active = false;

    ScreenTransitionPhase phase = ScreenTransitionPhase::None;
    ScreenTransitionAction action = ScreenTransitionAction::None;

    GameScreen targetScreen = GameScreen::MainMenu;

    float timer = 0.0f;
    float coverDuration = 0.75f;
    float uncoverDuration = 0.60f;

    bool midpointApplied = false;

    std::vector<TransitionShape> shapes;
};
