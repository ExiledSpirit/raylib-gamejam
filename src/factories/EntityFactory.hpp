#pragma once

#include <core/World.hpp>
#include "../components/BoxCollider2d.hpp"
#include "../components/Ball.hpp"
#include <ecs/components/Sprite.hpp>
#include "../components/Transform2d.hpp"
#include "../components/Velocity2d.hpp"

entt::entity CreatePlayerEntity(
    World& world,
    Sprite sprite,
    Transform2D transform,
    BoxCollider2D boxCollider
);

void CreateLaunchedBall(
    World& world,
    Vector2 spawnPosition,
    float finalPower
);