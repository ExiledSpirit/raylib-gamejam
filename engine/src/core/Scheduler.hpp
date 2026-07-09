#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include "Stage.hpp"
#include "World.hpp"

using SystemFn = std::function<void(World&)>;

class Scheduler
{
public:
    void AddSystem(
        Stage stage,
        SystemFn system
    );

    void RunStage(
        Stage stage,
        World& world
    );

private:
    std::unordered_map<
        Stage,
        std::vector<SystemFn>
    > systems;
};