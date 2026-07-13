#include "MainMenuUiSystem.hpp"

#include "../../resources/GameScreenResource.hpp"
#include "../../resources/MainMenuIntroResource.hpp"

#include <raylib.h>

#include <cmath>
#include <string>

static constexpr float SCREEN_WIDTH = 640.0f;
static constexpr float SCREEN_HEIGHT = 360.0f;

static void DrawTextCentered(
    const std::string& text,
    Vector2 center,
    int fontSize,
    Color color
)
{
    int width =
        MeasureText(
            text.c_str(),
            fontSize
        );

    DrawText(
        text.c_str(),
        static_cast<int>(std::floor(center.x - width * 0.5f)),
        static_cast<int>(std::floor(center.y - fontSize * 0.5f)),
        fontSize,
        color
    );
}

void MainMenuUiSystem(World& world)
{
    auto& screen =
        world.GetResource<GameScreenResource>();

    if(screen.current != GameScreen::MainMenu)
    {
        return;
    }

    auto& intro =
        world.GetResource<MainMenuIntroResource>();

    if(!intro.finished)
    {
        return;
    }

    float time =
        static_cast<float>(GetTime());

    float bob =
        std::sin(time * 2.0f) * 3.0f;

    DrawTextCentered(
        "PRESS START",
        Vector2{
            SCREEN_WIDTH * 0.5f,
            SCREEN_HEIGHT - 42.0f + bob
        },
        22,
        Color{0, 0, 0, 180}
    );

    DrawTextCentered(
        "PRESS START",
        Vector2{
            SCREEN_WIDTH * 0.5f,
            SCREEN_HEIGHT - 44.0f + bob
        },
        22,
        WHITE
    );
}
