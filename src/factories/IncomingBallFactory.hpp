#pragma once

#include <core/World.hpp>
#include <entt/entt.hpp>

entt::entity CreateIncomingBall(World& world);
void DestroyIncomingBalls(World& world);
