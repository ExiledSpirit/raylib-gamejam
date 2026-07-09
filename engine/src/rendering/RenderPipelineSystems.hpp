#pragma once

#include <core/World.hpp>

void BeginSceneRenderSystem(World& world);
void ScenePostProcessSystem(World& world);

void BeginUiRenderSystem(World& world);
void CompositeRenderSystem(World& world);

void PresentRenderSystem(World& world);
void ShutdownRenderSystem(World& world);
