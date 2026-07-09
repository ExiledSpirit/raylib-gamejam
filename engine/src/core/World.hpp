#pragma once

#include <entt/entt.hpp>

class World
{
public:
    entt::registry registry;

    template<typename T>
    T& GetResource()
    {
        return registry.ctx().get<T>();
    }

    template<typename T>
    T& InsertResource()
    {
        return registry.ctx().emplace<T>();
    }

    template<typename T>
    void InsertResource(const T& value)
    {
        registry.ctx().emplace<T>(value);
    }

    template<typename T>
    bool HasResource()
    {
        return registry.ctx().contains<T>();
    }
};