#include "InitializeResources.hpp"
#include "../resources/GameScreenResource.hpp"
#include <physics/PhysicsWorldResource.hpp>
#include <box2d/box2d.h>

void InitializeResources(World& world) {
    LoadGameScreenResource(world);
    LoadGamePhysicsResource(world);
}

void LoadGamePhysicsResource(World& world) {
    b2WorldDef worldDef = b2DefaultWorldDef();

    // Top-down golf-ish physics. No gravity.
    worldDef.gravity = b2Vec2{0.0f, 0.0f};

    auto& physics = world.InsertResource<PhysicsWorldResource>();
    physics.worldId = b2CreateWorld(&worldDef);
}

void LoadGameScreenResource(World& world) {
    auto gameScreenResource = GameScreenResource();
    world.InsertResource<GameScreenResource>(gameScreenResource);
}
