#include "SkillCheckUiSystem.hpp"

#include "../../resources/SkillCheckResource.hpp"
#include "../../utils/SkillCheckUtils.hpp"

#include <raylib.h>

#include <algorithm>
#include <cmath>

static float RadToDeg(float radians)
{
    return radians * 180.0f / SKILL_CHECK_PI;
}

static int GetSegmentsForArc(float angleSize)
{
    int segments =
        static_cast<int>(angleSize * 40.0f);

    return std::clamp(segments, 6, 64);
}

static void DrawRingSegmentRadians(
    Vector2 center,
    float innerRadius,
    float outerRadius,
    float startAngle,
    float endAngle,
    Color color
)
{
    startAngle =
        WrapSkillCheckAngle(startAngle);

    endAngle =
        WrapSkillCheckAngle(endAngle);

    float size =
        endAngle - startAngle;

    if(size < 0.0f)
    {
        size += SKILL_CHECK_TAU;
    }

    int segments =
        GetSegmentsForArc(size);

    if(startAngle <= endAngle)
    {
        DrawRing(
            center,
            innerRadius,
            outerRadius,
            RadToDeg(startAngle),
            RadToDeg(endAngle),
            segments,
            color
        );

        return;
    }

    DrawRing(
        center,
        innerRadius,
        outerRadius,
        RadToDeg(startAngle),
        360.0f,
        segments,
        color
    );

    DrawRing(
        center,
        innerRadius,
        outerRadius,
        0.0f,
        RadToDeg(endAngle),
        segments,
        color
    );
}

static void DrawOutlinedRingSegmentRadians(
    Vector2 center,
    float innerRadius,
    float outerRadius,
    float startAngle,
    float endAngle,
    Color fillColor,
    bool outlined,
    Color outlineColor,
    float outlineThickness
)
{
    if(outlined)
    {
        DrawRingSegmentRadians(
            center,
            innerRadius - outlineThickness,
            outerRadius + outlineThickness,
            startAngle,
            endAngle,
            outlineColor
        );
    }

    DrawRingSegmentRadians(
        center,
        innerRadius,
        outerRadius,
        startAngle,
        endAngle,
        fillColor
    );
}

void SkillCheckUiSystem(World& world)
{
    auto& skill =
        world.GetResource<SkillCheckResource>();

    if(!skill.active)
    {
        return;
    }

    DrawRing(
        skill.center,
        skill.innerRadius,
        skill.outerRadius,
        0.0f,
        360.0f,
        96,
        skill.ringColor
    );

    for(const SkillCheckTarget& target : skill.targets)
    {
        float startAngle =
            target.centerAngle - target.size * 0.5f;

        float endAngle =
            target.centerAngle + target.size * 0.5f;

        DrawOutlinedRingSegmentRadians(
            skill.center,
            skill.innerRadius,
            skill.outerRadius,
            startAngle,
            endAngle,
            target.color,
            target.outlined,
            target.outlineColor,
            target.outlineThickness
        );
    }

    float needleStart =
        skill.needleAngle - skill.needleWidth * 0.5f;

    float needleEnd =
        skill.needleAngle + skill.needleWidth * 0.5f;

    DrawRingSegmentRadians(
        skill.center,
        skill.innerRadius - 4.0f,
        skill.outerRadius + 4.0f,
        needleStart,
        needleEnd,
        skill.needleColor
    );

    DrawCircleLines(
        static_cast<int>(skill.center.x),
        static_cast<int>(skill.center.y),
        skill.innerRadius,
        Color{255, 255, 255, 80}
    );

    DrawCircleLines(
        static_cast<int>(skill.center.x),
        static_cast<int>(skill.center.y),
        skill.outerRadius,
        Color{255, 255, 255, 130}
    );
}