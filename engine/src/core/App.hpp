#pragma once

#include "AppConfig.hpp"
#include "Scheduler.hpp"
#include "World.hpp"

class App
{
public:
    explicit App(const AppConfig& config);

    void Run();
    void Frame();

    void AddSystem(Stage stage, SystemFn system);
    void AddStartupSystem(SystemFn system);

    World& GetWorld();

private:
    World world;
    Scheduler scheduler;
};