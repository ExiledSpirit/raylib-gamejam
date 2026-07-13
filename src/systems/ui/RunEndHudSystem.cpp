#include "RunEndHudSystem.hpp"

#include "../../resources/RunResource.hpp"
#include "../../resources/GameScreenResource.hpp"
#include "../../resources/RunEndAnimationResource.hpp"

#include <raylib.h>

#include <algorithm>
#include <cmath>
#include <string>

static constexpr float SCREEN_WIDTH = 640.0f;
static constexpr float SCREEN_HEIGHT = 360.0f;

static float EaseOutCubic(float t)
{
    t = std::clamp(t, 0.0f, 1.0f);

    float inv =
        1.0f - t;

    return 1.0f - inv * inv * inv;
}

static float EaseInCubic(float t)
{
    t = std::clamp(t, 0.0f, 1.0f);

    return t * t * t;
}

static void DrawTextCenteredRotated(
    const std::string& text,
    Vector2 center,
    float fontSize,
    float rotationDegrees,
    Color color
)
{
    Font font =
        GetFontDefault();

    Vector2 size =
        MeasureTextEx(
            font,
            text.c_str(),
            fontSize,
            1.0f
        );

    DrawTextPro(
        font,
        text.c_str(),
        Vector2{
            std::floor(center.x),
            std::floor(center.y)
        },
        Vector2{
            size.x * 0.5f,
            size.y * 0.5f
        },
        rotationDegrees,
        fontSize,
        1.0f,
        color
    );
}

static void DrawTextCentered(
    const std::string& text,
    Vector2 center,
    float fontSize,
    Color color
)
{
    DrawTextCenteredRotated(
        text,
        center,
        fontSize,
        0.0f,
        color
    );
}

static float GetEndlessTextY(float timer)
{
    constexpr float enterDuration = 0.75f;
    constexpr float holdDuration = 0.45f;
    constexpr float exitDuration = 0.75f;

    constexpr float startY = SCREEN_HEIGHT + 70.0f;
    constexpr float centerY = SCREEN_HEIGHT * 0.5f;
    constexpr float endY = -70.0f;

    if(timer < enterDuration)
    {
        float t =
            timer / enterDuration;

        float eased =
            EaseOutCubic(t);

        return startY + (centerY - startY) * eased;
    }

    if(timer < enterDuration + holdDuration)
    {
        return centerY;
    }

    float exitTimer =
        timer - enterDuration - holdDuration;

    float t =
        exitTimer / exitDuration;

    float eased =
        EaseInCubic(t);

    return centerY + (endY - centerY) * eased;
}

void RunEndHudSystem(World& world)
{
    auto& screen =
        world.GetResource<GameScreenResource>();

    if(screen.current != GameScreen::Playing)
    {
        return;
    }

    auto& run =
        world.GetResource<RunResource>();

    if(run.phase != RunPhase::MapLost &&
       run.phase != RunPhase::MapWon)
    {
        return;
    }

    auto& animation =
        world.GetResource<RunEndAnimationResource>();

    float time =
        animation.timer;

    if(run.phase == RunPhase::MapLost)
    {
        DrawRectangle(
            0,
            0,
            static_cast<int>(SCREEN_WIDTH),
            static_cast<int>(SCREEN_HEIGHT),
            Color{180, 0, 0, 180}
        );

        float bob =
            std::sin(time * 2.0f) * 5.0f;

        float rotation =
            std::sin(time * 1.7f) * 5.0f;

        Vector2 titleCenter{
            SCREEN_WIDTH * 0.5f,
            SCREEN_HEIGHT * 0.5f - 34.0f + bob
        };

        // Shadow
        DrawTextCenteredRotated(
            "GAME OVER",
            Vector2{
                titleCenter.x + 2.0f,
                titleCenter.y + 2.0f
            },
            34.0f,
            rotation,
            Color{0, 0, 0, 180}
        );

        DrawTextCenteredRotated(
            "GAME OVER",
            titleCenter,
            34.0f,
            rotation,
            Color{255, 90, 90, 255}
        );

        float promptBob =
            std::sin(time * 2.0f + 1.2f) * 3.0f;

        DrawTextCentered(
            "PRESS SPACE",
            Vector2{
                SCREEN_WIDTH * 0.5f,
                SCREEN_HEIGHT * 0.5f + 24.0f + promptBob
            },
            16,
            WHITE
        );

        return;
    }

    if(run.phase == RunPhase::MapWon)
    {
        float y =
            GetEndlessTextY(time);

        float scalePulse =
            1.0f + std::sin(time * 8.0f) * 0.035f;

        float fontSize =
            48.0f * scalePulse;

        Vector2 center{
            SCREEN_WIDTH * 0.5f,
            y
        };

        DrawTextCenteredRotated(
            "ENDLESS",
            Vector2{
                center.x + 3.0f,
                center.y + 3.0f
            },
            fontSize,
            0.0f,
            Color{0, 0, 0, 180}
        );

        DrawTextCenteredRotated(
            "ENDLESS",
            center,
            fontSize,
            0.0f,
            Color{255, 220, 90, 255}
        );
    }
}
