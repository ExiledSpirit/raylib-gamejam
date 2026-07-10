#include "DebugUiSystem.hpp"

#include "../../components/IncomingBall.hpp"
#include "../../components/Ball.hpp"
#include "../../components/BallPhysicsBody.hpp"
#include "../../components/Transform2D.hpp"

#include "../../resources/RunResource.hpp"
#include "../../resources/StrikeZonesResource.hpp"
#include "../../resources/SkillCheckResource.hpp"

#include "../../utils/DebugUtils.hpp"

#include <input/InputResource.hpp>

#include <raylib.h>
#include <box2d/box2d.h>

static int CountIncomingBalls(World& world)
{
    int count = 0;

    auto view = world.registry.view<IncomingBall>();

    for(auto entity : view)
    {
        (void)entity;
        count++;
    }

    return count;
}

static int CountActiveBalls(World& world)
{
    int count = 0;

    auto view = world.registry.view<Ball>();

    for(auto entity : view)
    {
        (void)entity;
        count++;
    }

    return count;
}

void DebugUiSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();
    auto& input = world.GetResource<InputResource>();

    int x = 8;
    int y = 8;
    int line = 10;

    DrawRectangle(
        4,
        4,
        250,
        130,
        Color{0, 0, 0, 180}
    );

    DrawText("DEBUG", x, y, 10, YELLOW);
    y += line + 2;

    DrawText(
        TextFormat("phase: %s", RunPhaseToString(run.phase)),
        x,
        y,
        10,
        WHITE
    );
    y += line;

    DrawText(
        TextFormat("phaseTimer: %.2f", run.phaseTimer),
        x,
        y,
        10,
        WHITE
    );
    y += line;

    DrawText(
        TextFormat(
            "throw down:%d pressed:%d released:%d",
            input.IsDown("throw"),
            input.IsPressed("throw"),
            input.IsReleased("throw")
        ),
        x,
        y,
        10,
        WHITE
    );
    y += line;

    DrawText(
        TextFormat("ballsRemaining: %d", run.ballsRemaining),
        x,
        y,
        10,
        WHITE
    );
    y += line;

    DrawText(
        TextFormat("incomingBall entities: %d", CountIncomingBalls(world)),
        x,
        y,
        10,
        WHITE
    );
    y += line;

    auto incomingView =
        world.registry.view<IncomingBall, Transform2D>();

    for(auto [entity, incoming, transform] : incomingView.each())
    {
        (void)entity;

        DrawText(
            TextFormat(
                "incoming pos: %.1f %.1f vel: %.1f %.1f groundY: %.1f",
                transform.position.x,
                transform.position.y,
                incoming.velocity.x,
                incoming.velocity.y,
                incoming.groundY
            ),
            x,
            y,
            10,
            GREEN
        );

        y += line;
    }

    DrawText(
        TextFormat("active ball entities: %d", CountActiveBalls(world)),
        x,
        y,
        10,
        WHITE
    );
    y += line;

    auto ballView =
        world.registry.view<Ball, BallPhysicsBody, Transform2D>();

    for(auto [entity, ball, physics, transform] : ballView.each())
    {
        (void)entity;
        (void)ball;

        b2Vec2 velocity{0.0f, 0.0f};

        if(b2Body_IsValid(physics.bodyId))
        {
            velocity = b2Body_GetLinearVelocity(physics.bodyId);
        }

        DrawText(
            TextFormat(
                "ball pos: %.1f %.1f vel: %.2f %.2f",
                transform.position.x,
                transform.position.y,
                velocity.x,
                velocity.y
            ),
            x,
            y,
            10,
            SKYBLUE
        );

        y += line;
    }
}