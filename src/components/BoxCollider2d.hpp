#pragma once

#include <raylib.h>

enum class ColliderType
{
    Solid,
    Trigger
};

struct BoxCollider2D
{
    Vector2 size;
    Vector2 offset;

    ColliderType type = ColliderType::Solid;
};
