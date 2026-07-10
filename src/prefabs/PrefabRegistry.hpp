#pragma once

#include <core/World.hpp>
#include <raylib.h>

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

struct PrefabDefinition
{
    std::string id;
    std::string displayName;

    Texture2D* previewTexture = nullptr;
    Rectangle previewSource{0, 0, 8, 8};

    std::function<entt::entity(World&, Vector2)> spawn;
};

class PrefabRegistry
{
public:
    void Register(PrefabDefinition prefab)
    {
        order.push_back(prefab.id);
        prefabs[prefab.id] = std::move(prefab);
    }

    entt::entity Spawn(
        World& world,
        const std::string& id,
        Vector2 position)
    {
        return prefabs.at(id).spawn(world, position);
    }

    const PrefabDefinition& Get(const std::string& id) const
    {
        return prefabs.at(id);
    }

    const std::vector<std::string>& GetIds() const
    {
        return order;
    }

private:
    std::unordered_map<std::string, PrefabDefinition> prefabs;
    std::vector<std::string> order;
};