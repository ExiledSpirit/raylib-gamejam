#include "CameraUpdateSystem.hpp"

#include "../../resources/GameCameraResource.hpp"

#include <ecs/resources/TimeResource.hpp>

#include <raymath.h>

#include <algorithm>
#include <cmath>

static void AddShakeContribution(
    Vector2& offset,
    float& rotation,
    float time,
    float frequency,
    float intensity,
    float maxOffset,
    float maxRotation
)
{
    constexpr float TAU = 6.28318530718f;

    float t = time * frequency * TAU;

    offset.x += std::sin(t + 1.37f) * maxOffset * intensity;
    offset.y += std::sin(t * 1.31f + 4.91f) * maxOffset * intensity;

    rotation += std::sin(t * 1.73f + 2.44f) * maxRotation * intensity;
}

static Vector2 ClampVectorLength(
    Vector2 value,
    float maxLength
)
{
    float length = Vector2Length(value);

    if(length <= maxLength || length <= 0.0001f)
    {
        return value;
    }

    return Vector2Scale(value, maxLength / length);
}

void CameraUpdateSystem(World& world)
{
    auto& camera = world.GetResource<GameCameraResource>();
    auto& time = world.GetResource<TimeResource>();

    float dt = time.deltaTime;

    float alpha = 1.0f - std::exp(-camera.speed * dt);

    camera.position = Vector2Lerp(
        camera.position,
        camera.target,
        alpha
    );

    camera.zoom +=
        (camera.targetZoom - camera.zoom) * alpha;

    camera.sustainedShakeIntensity +=
        (camera.targetSustainedShakeIntensity - camera.sustainedShakeIntensity)
        * alpha;

    camera.shakeTime += dt;

    Vector2 shakeOffset{0.0f, 0.0f};
    float shakeRotation = 0.0f;

    if(camera.sustainedShakeIntensity > 0.001f)
    {
        AddShakeContribution(
            shakeOffset,
            shakeRotation,
            camera.shakeTime,
            camera.sustainedShakeFrequency,
            camera.sustainedShakeIntensity,
            camera.sustainedShakeMaxOffset,
            camera.sustainedShakeMaxRotation
        );
    }

    for(auto it = camera.shakeBursts.begin(); it != camera.shakeBursts.end();)
    {
        it->age += dt;

        if(it->age >= it->duration)
        {
            it = camera.shakeBursts.erase(it);
            continue;
        }

        float life = 1.0f - (it->age / it->duration);
        float amount = it->intensity * life * life;

        AddShakeContribution(
            shakeOffset,
            shakeRotation,
            camera.shakeTime,
            it->frequency,
            amount,
            it->maxOffset,
            it->maxRotation
        );

        ++it;
    }

    camera.shakeOffset = ClampVectorLength(
        shakeOffset,
        camera.maxTotalShakeOffset
    );

    camera.shakeRotation = std::clamp(
        shakeRotation,
        -camera.maxTotalShakeRotation,
        camera.maxTotalShakeRotation
    );
}