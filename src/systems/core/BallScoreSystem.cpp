#include "BallScoreSystem.hpp"

#include "../../components/Ball.hpp"
#include "../../components/ShotScore.hpp"
#include "../../components/Transform2d.hpp"

#include "../../resources/RunResource.hpp"

#include "../../factories/FloatingTextFactory.hpp"

#include <raylib.h>
#include <raymath.h>

#include <string>

void BallScoreSystem(World& world)
{
    auto& run = world.GetResource<RunResource>();

    if(run.phase != RunPhase::BallRunning)
    {
        return;
    }

    auto view = world.registry.view<Ball, Transform2D, ShotScore>();

    for(auto [entity, ball, transform, score] : view.each())
    {
        (void)entity;
        (void)ball;

        if(score.finalized)
        {
            continue;
        }

        if(!score.initialized)
        {
            score.previousPosition = transform.position;
            score.initialized = true;

            score.distanceMeters = 0.0f;
            score.chips = 0;
            score.lastDisplayedChips = 0;
            score.mult = 1 + score.wallHits;
            score.finalScore = 0;

            continue;
        }

        Vector2 delta = Vector2Subtract(
            transform.position,
            score.previousPosition
        );

        float pixelDistance = Vector2Length(delta);

        score.distanceMeters += pixelDistance / PIXELS_PER_METER;
        score.previousPosition = transform.position;

        int newChips = static_cast<int>(score.distanceMeters);

        if(newChips > score.lastDisplayedChips)
        {
            int chipDelta = newChips - score.lastDisplayedChips;

            CreateFloatingText(
                world,
                "+" + std::to_string(chipDelta) + " chip",
                Vector2{
                    transform.position.x + 8.0f,
                    transform.position.y - 14.0f
                },
                SKYBLUE
            );

            score.lastDisplayedChips = newChips;
        }

        score.chips = newChips;
        score.mult = 1 + score.wallHits;
        score.finalScore = score.chips * score.mult;
    }
}