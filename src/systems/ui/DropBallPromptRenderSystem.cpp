#include "DropBallPromptRenderSystem.hpp"

#include "../../resources/RunResource.hpp"
#include "../../resources/GameScreenResource.hpp"

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

void DropBallPromptRenderSystem(World& world)
{
    auto& screen =
        world.GetResource<GameScreenResource>();

    if(screen.current != GameScreen::Playing)
    {
        return;
    }

    auto& run =
        world.GetResource<RunResource>();

    if(run.phase != RunPhase::WaitingToDropBall)
    {
        return;
    }

    float time =
        static_cast<float>(GetTime());

    float bob =
        std::sin(time * 2.0f) * 4.0f;

    Vector2 labelPosition{
        SCREEN_WIDTH * 0.5f,
        SCREEN_HEIGHT * 0.5f + bob
    };

    DrawTextCentered(
        "PRESS SPACE",
        Vector2{
            labelPosition.x + 1.0f,
            labelPosition.y + 1.0f
        },
        28,
        Color{40, 40, 40, 180}
    );

    DrawTextCentered(
        "PRESS SPACE",
        labelPosition,
        28,
        WHITE
    );
}