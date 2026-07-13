#include "ScreenTransitionRenderSystem.hpp"

#include "../../resources/ScreenTransitionResource.hpp"

#include <raylib.h>
#include <raymath.h>

#include <algorithm>
#include <cmath>

static float EaseInOut(float t)
{
    return t * t * (3.0f - 2.0f * t);
}

void ScreenTransitionRenderSystem(World& world)
{
    auto& transition = world.GetResource<ScreenTransitionResource>();

    if(!transition.active)
    {
        return;
    }

    float t = 0.0f;

    if(transition.phase == ScreenTransitionPhase::Covering)
    {
        t = transition.timer / transition.coverDuration;
    }
    else if(transition.phase == ScreenTransitionPhase::Uncovering)
    {
        t = 1.0f - transition.timer / transition.uncoverDuration;
    }

    t = std::clamp(t, 0.0f, 1.0f);
    t = EaseInOut(t);

    for(const TransitionShape& shape : transition.shapes)
    {
        float size =
            Lerp(shape.startSize, shape.endSize, t);

        DrawPoly(
            shape.position,
            shape.sides,
            size,
            shape.rotation,
            shape.color
        );
    }
}