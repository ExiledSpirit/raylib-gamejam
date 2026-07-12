#include "FloatingTextFactory.hpp"

#include "../components/FloatingText.hpp"
#include "../components/Transform2D.hpp"

void CreateFloatingText(
    World& world,
    const std::string& text,
    Vector2 position,
    Color color,
    float lifetime,
    int fontSize
)
{
    auto entity = world.registry.create();

    auto& transform = world.registry.emplace<Transform2D>(entity);
    transform.position = position;

    auto& floatingText = world.registry.emplace<FloatingText>(entity);
    floatingText.text = text;
    floatingText.color = color;
    floatingText.lifetime = lifetime;
    floatingText.fontSize = fontSize;
}
