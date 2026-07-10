#include "DebugIncomingBallRenderSystem.hpp"

#include "../../components/IncomingBall.hpp"
#include "../../components/Transform2D.hpp"
#include "../../resources/RunResource.hpp"

#include <raylib.h>

void DebugIncomingBallRenderSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();

    if(run.phase != RunPhase::BallFalling)
    {
        return;
    }

    auto view =
        world.registry.view<IncomingBall, Transform2D>();

    for(auto [entity, incoming, transform] : view.each())
    {
        (void)entity;

        DrawCircleV(
            transform.position,
            incoming.radius,
            RED
        );

        DrawCircleLines(
            static_cast<int>(transform.position.x),
            static_cast<int>(transform.position.y),
            incoming.radius + 2.0f,
            YELLOW
        );
    }
}