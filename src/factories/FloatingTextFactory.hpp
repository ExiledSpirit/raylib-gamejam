#pragma once

#include <core/World.hpp>

#include <raylib.h>
#include <string>

void CreateFloatingText(
    World& world,
    const std::string& text,
    Vector2 position,
    Color color
);