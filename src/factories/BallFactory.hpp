#pragma once

#include <core/World.hpp>
#include <box2d/box2d.h>


static b2BodyId CreateBallBody(
    b2WorldId worldId,
    b2Vec2 position,
    float radius
);

entt::entity CreateBall(
    World& world,
    b2Vec2 positionMeters
);
