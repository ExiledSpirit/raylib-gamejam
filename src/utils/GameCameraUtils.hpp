#pragma once

#include "../resources/GameCameraResource.hpp"

#include <raylib.h>
#include <raymath.h>

inline Camera2D BuildRaylibCamera2D(
    const GameCameraResource& camera,
    int internalWidth,
    int internalHeight
)
{
    Camera2D rayCamera{};

    rayCamera.offset = Vector2{
        internalWidth / 2.0f,
        internalHeight / 2.0f
    };

    rayCamera.target = Vector2Add(
        camera.position,
        camera.shakeOffset
    );

    rayCamera.rotation = camera.shakeRotation;
    rayCamera.zoom = camera.zoom;

    return rayCamera;
}