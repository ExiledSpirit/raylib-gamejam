#include "BallPhysicsSyncSystem.hpp"

#include <core/World.hpp>
#include <physics/PhysicsUnits.hpp>

#include "../../components/BallPhysicsBody.hpp"
#include "../../components/Ball.hpp"
#include "../../components/Transform2D.hpp"

#include <box2d/box2d.h>

void BallPhysicsSyncSystem(World& world)
{
    auto view = world.registry.view<Ball, BallPhysicsBody, Transform2D>();

    for(auto [entity, ball, body, transform] : view.each())
    {
        if(!b2Body_IsValid(body.bodyId))
        {
            continue;
        }

        b2Vec2 position = b2Body_GetPosition(body.bodyId);

        transform.position = ToPixels(position);

        b2Rot rotation = b2Body_GetRotation(body.bodyId);

        // b2Rot stores cosine/sine.
        transform.rotation = atan2f(rotation.s, rotation.c);
    }
}
