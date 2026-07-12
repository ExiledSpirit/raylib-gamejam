#include "RewardPopupRenderSystem.hpp"

#include "../../resources/RewardPopupResource.hpp"
#include "../../resources/FontResource.hpp"
#include "../../resources/RunResource.hpp"

#include <raylib.h>

#include <algorithm>
#include <cmath>
#include <string>

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
        MeasureTextEx(font, text.c_str(), fontSize, 1.0f);

    DrawText(
        text.c_str(),
        std::floor(center.x - size.x * 0.5f),
        std::floor(center.y - size.y * 0.5f),
        fontSize,
        color
    );
}

void RewardPopupRenderSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();

    if(run.phase != RunPhase::LevelReward)
    {
        return;
    }

    auto& popup = world.GetResource<RewardPopupResource>();
    auto& fonts = world.GetResource<FontResource>();

    if(!popup.active)
    {
        return;
    }

    float fontSize = 10.0f;
    float rowHeight = 14.0f;

    float maxLabelWidth = 0.0f;
    float maxDollarWidth = 0.0f;

    for(const RewardPopupLine& line : popup.lines)
    {
        Vector2 labelSize =
            MeasureTextEx(fonts.hud, line.label.c_str(), fontSize, 1.0f);

        std::string dollars =
            RepeatDollar(line.gold);

        Vector2 dollarSize =
            MeasureTextEx(fonts.hud, dollars.c_str(), fontSize, 1.0f);

        maxLabelWidth =
            std::max(maxLabelWidth, labelSize.x);

        maxDollarWidth =
            std::max(maxDollarWidth, dollarSize.x);
    }

    float paddingX = 16.0f;
    float paddingY = 14.0f;
    float gap = 24.0f;
    float buttonHeight = 20.0f;

    float cardWidth =
        paddingX * 2.0f +
        maxLabelWidth +
        gap +
        maxDollarWidth;

    cardWidth =
        std::max(cardWidth, 120.0f);

    float cardHeight =
        paddingY * 2.0f +
        buttonHeight +
        8.0f +
        popup.lines.size() * rowHeight +
        10.0f;

    float cardX =
        std::floor(256.0f - cardWidth * 0.5f);

    float cardY =
        std::floor(144.0f - cardHeight * 0.5f);

    DrawRectangle(
        static_cast<int>(cardX),
        static_cast<int>(cardY),
        static_cast<int>(cardWidth),
        static_cast<int>(cardHeight),
        Color{10, 10, 14, 230}
    );

    DrawRectangleLines(
        static_cast<int>(cardX),
        static_cast<int>(cardY),
        static_cast<int>(cardWidth),
        static_cast<int>(cardHeight),
        Color{255, 255, 255, 120}
    );

    if(popup.buttonVisible)
    {
        Rectangle buttonRect{
            cardX + cardWidth * 0.5f - 34.0f,
            cardY + 8.0f,
            68.0f,
            16.0f
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
            fonts.hud,
            "TO SHOP",
            Vector2{
                buttonRect.x + buttonRect.width * 0.5f,
                buttonRect.y + buttonRect.height * 0.5f
            },
            9.0f,
            Color{40, 25, 10, 255}
        );
    }

    float rowY =
        cardY + paddingY + buttonHeight + 12.0f;

    float labelX =
        cardX + paddingX;

    float dollarRightX =
        cardX + cardWidth - paddingX;

    for(const RewardPopupLine& line : popup.lines)
    {
        std::string label =
            VisibleText(line.label, line.visibleChars);

        std::string dollars =
            VisibleText(
                RepeatDollar(line.gold),
                line.visibleChars
            );

        DrawText(
            label.c_str(),
            std::floor(labelX),
            std::floor(rowY),
            fontSize,
            WHITE
        );

        Vector2 dollarSize =
            MeasureTextEx(fonts.hud, dollars.c_str(), fontSize, 1.0f);

        DrawText(
            dollars.c_str(),
            std::floor(dollarRightX - dollarSize.x),
            std::floor(rowY),
            fontSize,
            GOLD
        );

        rowY += rowHeight;
    }

    std::string total =
        "TOTAL " + RepeatDollar(popup.totalGold);

    DrawTextCentered(
        fonts.hud,
        total,
        Vector2{
            cardX + cardWidth * 0.5f,
            cardY + cardHeight - 12.0f
        },
        10.0f,
        GOLD
    );
}
