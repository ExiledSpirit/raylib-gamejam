#include "Scheduler.hpp"

void Scheduler::AddSystem(
    Stage stage,
    SystemFn system
)
{
    systems[stage].push_back(system);
}

void Scheduler::RunStage(
    Stage stage,
    World& world
)
{
    auto it = systems.find(stage);

    if(it == systems.end())
    {
        return;
    }

    for(auto& system : it->second)
    {
        system(world);
    }
}