#include "BallScoreSystem.hpp"

#include <ecs/resources/TimeResource.hpp>

#include "../../components/Ball.hpp"
#include "../../components/ShotScore.hpp"
#include "../../components/Transform2d.hpp"

#include <raymath.h>

void BallScoreSystem(World& world)
{
    auto& time = world.GetResource<TimeResource>();

    auto view = world.registry.view<Ball, Transform2D, ShotScore>();

    for(auto [entity, ball, transform, score] : view.each())
    {
        if(!score.initialized)
        {
            score.previousPosition = transform.position;
            score.initialized = true;
            continue;
        }

        Vector2 delta = Vector2Subtract(
            transform.position,
            score.previousPosition
        );

        float pixelDistance = Vector2Length(delta);

        score.distanceMeters += pixelDistance / PIXELS_PER_METER;
        score.previousPosition = transform.position;

        if(score.wallHitCooldown > 0.0f)
        {
            score.wallHitCooldown -= time.deltaTime;
        }

        score.chips = static_cast<int>(score.distanceMeters);
        score.mult = 1 + score.wallHits;
        score.finalScore = score.chips * score.mult;
    }
}