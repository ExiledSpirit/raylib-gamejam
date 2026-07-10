#include "SkillCheckUiSystem.hpp"

#include <raylib.h>
#include "../../resources/RunResource.hpp"
#include "../../resources/SkillCheckResource.hpp"

void SkillCheckUiSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();

    if(run.phase != RunPhase::SkillChecks)
    {
        return;
    }

    auto& skill = world.GetResource<SkillCheckResource>();

    Vector2 center{256.0f, 144.0f};
    float radius = 38.0f;

    DrawCircleLinesV(center, radius, WHITE);

    // Good zone
    DrawCircleSectorLines(
        center,
        radius,
        (skill.zoneCenterAngle - skill.goodZoneSize * 0.5f) * RAD2DEG,
        (skill.zoneCenterAngle + skill.goodZoneSize * 0.5f) * RAD2DEG,
        16,
        YELLOW
    );

    // Great zone
    DrawCircleSectorLines(
        center,
        radius + 3.0f,
        (skill.zoneCenterAngle - skill.greatZoneSize * 0.5f) * RAD2DEG,
        (skill.zoneCenterAngle + skill.greatZoneSize * 0.5f) * RAD2DEG,
        16,
        GREEN
    );

    Vector2 needleEnd{
        center.x + std::cos(skill.needleAngle) * radius,
        center.y + std::sin(skill.needleAngle) * radius
    };

    DrawLineEx(center, needleEnd, 2.0f, RED);

    DrawText(
        TextFormat("%d / %d", skill.currentEvent + 1, skill.totalEvents),
        244,
        190,
        10,
        WHITE
    );
}
