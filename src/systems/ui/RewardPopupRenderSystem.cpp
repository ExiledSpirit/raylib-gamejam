#include "RewardPopupRenderSystem.hpp"

#include "../../resources/RewardPopupResource.hpp"
#include "../../resources/FontResource.hpp"
#include "../../resources/RunResource.hpp"

#include <raylib.h>

#include <algorithm>
#include <cmath>
#include <string>

static constexpr float SCREEN_WIDTH = 640.0f;
static constexpr float SCREEN_HEIGHT = 360.0f;

static constexpr Vector2 SCREEN_CENTER{
    SCREEN_WIDTH * 0.5f,
    SCREEN_HEIGHT * 0.5f
};

static std::string RepeatDollar(int amount)
{
    return std::string(amount, '$');
}

static std::string VisibleText(
    const std::string& text,
    int visibleChars
)
{
    int count =
        std::clamp(
            visibleChars,
            0,
            static_cast<int>(text.size())
        );

    return text.substr(0, count);
}

static void DrawTextCentered(
    Font font,
    const std::string& text,
    Vector2 center,
    float fontSize,
    Color color
)
{
    Vector2 size =
        MeasureTextEx(
            font,
            text.c_str(),
            fontSize,
            1.0f
        );

    DrawText(
        text.c_str(),
        std::floor(center.x - size.x * 0.5f),
        std::floor(center.y - size.y * 0.5f),
        fontSize,
        color
    );
}

static void DrawTextLeft(
    Font font,
    const std::string& text,
    Vector2 position,
    float fontSize,
    Color color
)
{
    DrawText(
        text.c_str(),
        std::floor(position.x),
        std::floor(position.y),
        fontSize,
        color
    );
}

static void DrawTextRight(
    Font font,
    const std::string& text,
    Vector2 rightPosition,
    float fontSize,
    Color color
)
{
    Vector2 size =
        MeasureTextEx(
            font,
            text.c_str(),
            fontSize,
            1.0f
        );

    DrawText(
        text.c_str(),
        std::floor(rightPosition.x - size.x),
        std::floor(rightPosition.y),
        fontSize,
        color
    );
}

void RewardPopupRenderSystem(World& world)
{
    auto& run =
        world.GetResource<RunResource>();

    if(run.phase != RunPhase::LevelReward)
    {
        return;
    }

    auto& popup =
        world.GetResource<RewardPopupResource>();

    auto& fonts =
        world.GetResource<FontResource>();

    if(!popup.active)
    {
        return;
    }

    Font font =
        fonts.hud;

    constexpr float fontSize = 12.0f;
    constexpr float totalFontSize = 12.0f;
    constexpr float buttonFontSize = 10.0f;

    constexpr float rowHeight = 17.0f;

    float maxLabelWidth = 0.0f;
    float maxDollarWidth = 0.0f;

    for(const RewardPopupLine& line : popup.lines)
    {
        Vector2 labelSize =
            MeasureTextEx(
                font,
                line.label.c_str(),
                fontSize,
                1.0f
            );

        std::string dollars =
            RepeatDollar(line.gold);

        Vector2 dollarSize =
            MeasureTextEx(
                font,
                dollars.c_str(),
                fontSize,
                1.0f
            );

        maxLabelWidth =
            std::max(maxLabelWidth, labelSize.x);

        maxDollarWidth =
            std::max(maxDollarWidth, dollarSize.x);
    }

    constexpr float paddingX = 22.0f;
    constexpr float paddingY = 18.0f;
    constexpr float gap = 38.0f;

    constexpr float buttonWidth = 86.0f;
    constexpr float buttonHeight = 20.0f;

    constexpr float buttonTopGap = 8.0f;
    constexpr float rowsTopGap = 18.0f;
    constexpr float totalBottomGap = 20.0f;

    float cardWidth =
        paddingX * 2.0f +
        maxLabelWidth +
        gap +
        maxDollarWidth;

    cardWidth =
        std::max(cardWidth, 190.0f);

    cardWidth =
        std::max(cardWidth, buttonWidth + paddingX * 2.0f);

    float rowsHeight =
        static_cast<float>(popup.lines.size()) * rowHeight;

    float cardHeight =
        paddingY +
        buttonHeight +
        rowsTopGap +
        rowsHeight +
        totalBottomGap +
        paddingY;

    cardHeight =
        std::max(cardHeight, 126.0f);

    float cardX =
        std::floor(SCREEN_CENTER.x - cardWidth * 0.5f);

    float cardY =
        std::floor(SCREEN_CENTER.y - cardHeight * 0.5f);

    Rectangle cardRect{
        cardX,
        cardY,
        cardWidth,
        cardHeight
    };

    DrawRectangleRec(
        cardRect,
        Color{10, 10, 14, 235}
    );

    DrawRectangleLinesEx(
        cardRect,
        2.0f,
        Color{255, 255, 255, 130}
    );

    // Subtle inner line.
    DrawRectangleLinesEx(
        Rectangle{
            cardX + 3.0f,
            cardY + 3.0f,
            cardWidth - 6.0f,
            cardHeight - 6.0f
        },
        1.0f,
        Color{255, 255, 255, 45}
    );

    float buttonY =
        cardY + paddingY - 4.0f;

    if(popup.buttonVisible)
    {
        Rectangle buttonRect{
            std::floor(cardX + cardWidth * 0.5f - buttonWidth * 0.5f),
            std::floor(buttonY),
            buttonWidth,
            buttonHeight
        };

        DrawRectangleRec(
            buttonRect,
            Color{230, 200, 90, 255}
        );

        DrawRectangleLinesEx(
            buttonRect,
            1.0f,
            Color{80, 50, 20, 255}
        );

        DrawTextCentered(
            font,
            "TO SHOP",
            Vector2{
                buttonRect.x + buttonRect.width * 0.5f,
                buttonRect.y + buttonRect.height * 0.5f
            },
            buttonFontSize,
            Color{40, 25, 10, 255}
        );
    }
    else
    {
        Rectangle buttonRect{
            std::floor(cardX + cardWidth * 0.5f - buttonWidth * 0.5f),
            std::floor(buttonY),
            buttonWidth,
            buttonHeight
        };

        DrawRectangleLinesEx(
            buttonRect,
            1.0f,
            Color{255, 255, 255, 45}
        );
    }

    float rowY =
        cardY +
        paddingY +
        buttonHeight +
        rowsTopGap;

    float labelX =
        cardX + paddingX;

    float dollarRightX =
        cardX + cardWidth - paddingX;

    for(const RewardPopupLine& line : popup.lines)
    {
        std::string label =
            VisibleText(
                line.label,
                line.visibleChars
            );

        std::string dollars =
            VisibleText(
                RepeatDollar(line.gold),
                line.visibleChars
            );

        DrawTextLeft(
            font,
            label,
            Vector2{labelX, rowY},
            fontSize,
            WHITE
        );

        DrawTextRight(
            font,
            dollars,
            Vector2{dollarRightX, rowY},
            fontSize,
            GOLD
        );

        rowY += rowHeight;
    }

    std::string total =
        "TOTAL " + RepeatDollar(popup.totalGold);

    DrawTextCentered(
        font,
        total,
        Vector2{
            cardX + cardWidth * 0.5f,
            cardY + cardHeight - paddingY + 2.0f
        },
        totalFontSize,
        GOLD
    );
}