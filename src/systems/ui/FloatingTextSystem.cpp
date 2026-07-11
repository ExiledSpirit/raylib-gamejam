#include "FloatingTextSystem.hpp"

#include "../../components/FloatingText.hpp"
#include "../../components/Transform2D.hpp"

#include <ecs/resources/TimeResource.hpp>

void FloatingTextSystem(World& world)
{
    auto& time = world.GetResource<TimeResource>();

    auto view = world.registry.view<FloatingText, Transform2D>();

    for(auto [entity, text, transform] : view.each())
    {
        text.age += time.deltaTime;

        transform.position.x += text.velocity.x * time.deltaTime;
        transform.position.y += text.velocity.y * time.deltaTime;

        if(text.age >= text.lifetime)
        {
            world.registry.destroy(entity);
        }
    }
}