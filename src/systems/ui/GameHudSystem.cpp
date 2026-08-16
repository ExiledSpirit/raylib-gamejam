#include "GameHudSystem.hpp"

#include "../../resources/RunResource.hpp"
#include "../../resources/HudAnimationResource.hpp"
#include "../../resources/FontResource.hpp"
#include "../../resources/CampaignResource.hpp"
#include "../../resources/EconomyResource.hpp"

#include "../../components/ShotScore.hpp"
#include "../../components/Ball.hpp"

#include "../../utils/MathHelper.hpp"

#include <raylib.h>

#include <algorithm>
#include <cmath>
#include <string>

struct ShotHudTotals
{
    bool hasActiveShot = false;
    __int128_t chips = 0;
    int wallHits = 0;
    __int128_t mult = 0;
    __int128_t finalScore = 0;
};

static ShotHudTotals GetCurrentShotTotals(World& world)
{
    ShotHudTotals totals{};

    auto view =
        world.registry.view<Ball, ShotScore>();

    for(auto [entity, ball, score] : view.each())
    {
        (void)entity;
        (void)ball;

        totals.hasActiveShot = true;

        totals.chips += score.chips;
        totals.wallHits += score.mult;
    }

    if(totals.hasActiveShot)
    {
        totals.mult = 1 + totals.wallHits;
        totals.finalScore = totals.chips * totals.mult;
    }

    return totals;
}

static float GetPulseScale(const HudPulse& pulse)
{
    if(pulse.timer <= 0.0f)
    {
        return 1.0f;
    }

    float t = pulse.timer / pulse.duration;

    float bump =
        std::sin(t * 3.14159265f);

    return 1.0f + bump * pulse.strength;
}

static void DrawTextCentered(
    Font font,
    const std::string& text,
    Vector2 center,
    float fontSize,
    float spacing,
    Color color
)
{
    Vector2 size =
        MeasureTextEx(
            font,
            text.c_str(),
            fontSize,
            spacing
        );

    DrawText(
        text.c_str(),
        std::floor(center.x - size.x * 0.5f),
        std::floor(center.y - size.y * 0.5f),
        fontSize,
        color
    );
}

static void DrawTextRightAligned(
    Font font,
    const std::string& text,
    Vector2 rightCenter,
    float fontSize,
    float spacing,
    Color color
)
{
    Vector2 size =
        MeasureTextEx(
            font,
            text.c_str(),
            fontSize,
            spacing
        );

    DrawText(
        text.c_str(),
        std::floor(rightCenter.x - size.x),
        std::floor(rightCenter.y - size.y * 0.5f),
        fontSize,
        color
    );
}

static void DrawTextLeftAligned(
    Font font,
    const std::string& text,
    Vector2 leftCenter,
    float fontSize,
    float spacing,
    Color color
)
{
    Vector2 size =
        MeasureTextEx(
            font,
            text.c_str(),
            fontSize,
            spacing
        );

    DrawText(
        text.c_str(),
        std::floor(leftCenter.x),
        std::floor(leftCenter.y - size.y * 0.5f),
        fontSize,
        color
    );
}

static void DrawPulsingTextCentered(
    Font font,
    const std::string& text,
    Vector2 center,
    float baseFontSize,
    const HudPulse& pulse,
    Color color
)
{
    float scale =
        GetPulseScale(pulse);

    DrawTextCentered(
        font,
        text,
        center,
        baseFontSize * scale,
        1.0f,
        color
    );
}

static void DrawPulsingTextRightAligned(
    Font font,
    const std::string& text,
    Vector2 rightCenter,
    float baseFontSize,
    const HudPulse& pulse,
    Color color
)
{
    float scale =
        GetPulseScale(pulse);

    DrawTextRightAligned(
        font,
        text,
        rightCenter,
        baseFontSize * scale,
        1.0f,
        color
    );
}

static void DrawPulsingTextLeftAligned(
    Font font,
    const std::string& text,
    Vector2 leftCenter,
    float baseFontSize,
    const HudPulse& pulse,
    Color color
)
{
    float scale =
        GetPulseScale(pulse);

    DrawTextLeftAligned(
        font,
        text,
        leftCenter,
        baseFontSize * scale,
        1.0f,
        color
    );
}

void GameHudSystem(World& world)
{
    auto& run =
        world.GetResource<RunResource>();

    auto& hud =
        world.GetResource<HudAnimationResource>();

    auto& fonts =
        world.GetResource<FontResource>();
    auto& economy =
        world.GetResource<EconomyResource>();
    auto& campaign =
        world.GetResource<CampaignResource>();

    ShotHudTotals shotTotals =
        GetCurrentShotTotals(world);

    __int128_t chips =
        shotTotals.chips;

    __int128_t mult =
        shotTotals.mult;

    __int128_t displayedScore =
        run.currentScore;

    float progress = 0.0f;

    if(run.requiredScore > 0)
    {
        progress =
            static_cast<float>(displayedScore) /
            static_cast<float>(run.requiredScore);
    }

    progress =
        std::clamp(progress, 0.0f, 1.0f);

    // chips x mult
    // Chips are right-aligned so they grow to the left.
    Vector2 chipsRight{52.0f, 180.0f};
    Vector2 xCenter{60.0f, 180.0f};
    Vector2 multLeft{68.0f, 180.0f};

    DrawPulsingTextRightAligned(
        fonts.hud,
        FormatScore(chips),
        chipsRight,
        22.0f,
        hud.chipsPulse,
        SKYBLUE
    );

    DrawTextCentered(
        fonts.hud,
        "x",
        xCenter,
        22.0f,
        1.0f,
        WHITE
    );

    DrawPulsingTextLeftAligned(
        fonts.hud,
        FormatScore(mult),
        multLeft,
        22.0f,
        hud.multPulse,
        ORANGE
    );

    // Flying payout number
    if(hud.payout.active)
    {
        DrawPulsingTextCentered(
            fonts.hud,
            "+" + FormatScore(hud.payout.amount),
            hud.payout.position,
            18.0f,
            hud.payoutPulse,
            YELLOW
        );
    }
    
    DrawText(
        TextFormat("$%d", economy.gold),
        xCenter.x + 20.f,
        xCenter.y + 24.f,
        20,
        GOLD
    );
    
    DrawText(
        "REMAINING",
        8,
        xCenter.y + 20.f,
        10,
        Color{180, 180, 180, 255}
    );

    DrawText(
        "BALLS",
        8,
        xCenter.y + 30.f,
        10,
        Color{180, 180, 180, 255}
    );

    DrawPulsingTextCentered(
        fonts.hud,
        std::to_string(run.ballsRemaining),
        Vector2{50.0f, xCenter.y + 40.0f},
        18.0f,
        hud.ballsPulse,
        WHITE
    );

    Vector2 barOffset{0.0f, 0.0f};

    if(hud.barShakeTimer > 0.0f)
    {
        float life =
            hud.barShakeTimer / hud.barShakeDuration;

        float amount =
            life * hud.barShakeStrength;

        barOffset.x =
            std::sin(hud.time * 36.0f) * 2.0f * amount;

        barOffset.y =
            std::sin(hud.time * 29.0f + 1.7f) * 1.0f * amount;
    }

    if(run.currentScore >= run.requiredScore)
    {
        barOffset.x +=
            std::sin(hud.time * 8.0f) * 1.0f;

        barOffset.y +=
            std::sin(hud.time * 6.0f) * 0.5f;
    }

    int barX =
        static_cast<int>(8 + barOffset.x);

    int barY =
        static_cast<int>(130 + barOffset.y);

    int barW = 100;
    int barH = 24;

    DrawRectangle(
        barX,
        barY,
        barW,
        barH,
        Color{20, 20, 24, 220}
    );

    DrawRectangleLines(
        barX,
        barY,
        barW,
        barH,
        Color{255, 255, 255, 100}
    );

    int fillW =
        static_cast<int>((barW - 4) * progress);

    DrawRectangle(
        barX + 2,
        barY + 2,
        fillW,
        barH - 4,
        Color{120, 220, 140, 255}
    );
    
    // Score text: only committed score, not preview score.
    DrawPulsingTextCentered(
        fonts.hud,
        FormatScore(displayedScore) + " / " + FormatScore(run.requiredScore),
        Vector2{
            static_cast<float>(barX + (barW/2)),
            static_cast<float>(barY + (barH/2))
        },
        10.0f,
        hud.scorePulse,
        WHITE
    );

    
    DrawText(
        "ACT",
        8,
        barY - 40.f,
        10,
        Color{180, 180, 180, 255}
    );

    DrawText(
        TextFormat("%i/%i", campaign.act, campaign.maxActs),
        8,
        barY - 28.f,
        20,
        WHITE
    );
    
    DrawText(
        "GAME",
        60,
        barY - 40.f,
        10,
        Color{180, 180, 180, 255}
    );

    DrawText(
        TextFormat("%i", campaign.level),
        70,
        barY - 28.f,
        20,
        WHITE
    );
}
