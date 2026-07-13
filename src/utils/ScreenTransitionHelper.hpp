#pragma once

#include "../resources/ScreenTransitionResource.hpp"

#include <raylib.h>

// silly random shape for screen transition
inline void RequestScreenTransition(
    ScreenTransitionResource& transition,
    GameScreen targetScreen,
    ScreenTransitionAction action
)
{
    transition.active = true;
    transition.phase = ScreenTransitionPhase::Covering;
    transition.action = action;
    transition.targetScreen = targetScreen;

    transition.timer = 0.0f;
    transition.midpointApplied = false;
    transition.shapes.clear();

    constexpr int shapeCount = 12;

    for(int i = 0; i < shapeCount; ++i)
    {
        TransitionShape shape{};

        shape.position = Vector2{
            static_cast<float>(GetRandomValue(0, 640)),
            static_cast<float>(GetRandomValue(0, 360))
        };

        shape.startSize = static_cast<float>(GetRandomValue(8, 30));
        shape.endSize = static_cast<float>(GetRandomValue(420, 900));
        shape.rotation = static_cast<float>(GetRandomValue(0, 360));
        shape.sides = GetRandomValue(3, 4); // triangle or square/diamond

        shape.color = Color{8, 8, 12, 255};

        transition.shapes.push_back(shape);
    }
}
