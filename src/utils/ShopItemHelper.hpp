#pragma once

#include <raylib.h>
#include "../resources/SkillCheckResource.hpp"
#include "../resources/ShopResource.hpp"
#include "../resources/PowerUpDatabaseResource.hpp"
#include "PlayerStatsHelper.hpp"

#include <vector>
#include <string>
#include <cmath>

static constexpr float SHOP_ANGLE_RIGHT = 0.0f;
static constexpr float SHOP_ANGLE_BOTTOM = 1.5707963f;
static constexpr float SHOP_ANGLE_LEFT = 3.1415926f;
static constexpr float SHOP_ANGLE_TOP = 4.7123890f;

inline SkillCheckTarget CreateShopItemTarget(
    int slotIndex,
    float angle,
    int price
)
{
    SkillCheckTarget target{};

    target.id = "shop_slot_" + std::to_string(slotIndex);
    target.label = "Item";
    target.kind = SkillCheckTargetKind::ShopItem;

    target.centerAngle = angle;
    target.size = 2.5f;
    target.priority = 2;

    target.itemIndex = slotIndex;
    target.goldCost = price;

    target.color = Color{90, 180, 255, 220};
    target.outlined = true;
    target.outlineColor = WHITE;
    target.outlineThickness = 2.0f;

    return target;
}

inline SkillCheckTarget CreateShopRerollTarget(int cost)
{
    SkillCheckTarget target{};

    target.id = "reroll";
    target.label = "Reroll";
    target.kind = SkillCheckTargetKind::Reroll;

    target.centerAngle = SHOP_ANGLE_TOP;
    target.size = 0.55f;
    target.priority = 1;

    target.goldCost = cost;

    target.color = Color{255, 170, 70, 230};
    target.outlined = true;
    target.outlineColor = WHITE;
    target.outlineThickness = 2.0f;

    return target;
}

inline SkillCheckTarget CreateShopExitTarget()
{
    SkillCheckTarget target{};

    target.id = "exit";
    target.label = "Exit";
    target.kind = SkillCheckTargetKind::Exit;

    target.centerAngle = SHOP_ANGLE_BOTTOM;
    target.size = 0.55f;
    target.priority = 1;

    target.color = Color{255, 90, 90, 230};
    target.outlined = true;
    target.outlineColor = WHITE;
    target.outlineThickness = 2.0f;

    return target;
}

inline std::vector<SkillCheckTarget> CreateShopSkillCheckTargets(
    const ShopResource& shop,
    const PowerUpDatabaseResource& database
)
{
    std::vector<SkillCheckTarget> targets;

    targets.push_back(CreateShopRerollTarget(shop.rerollCost));
    targets.push_back(CreateShopExitTarget());

    if(shop.slots.size() > 0)
    {
        const PowerUpDefinition* definition =
            FindPowerUp(database, shop.slots[0].powerUpId);

        int price = definition != nullptr ? definition->price : 0;

        targets.push_back(
            CreateShopItemTarget(0, SHOP_ANGLE_LEFT, price)
        );
    }

    if(shop.slots.size() > 1)
    {
        const PowerUpDefinition* definition =
            FindPowerUp(database, shop.slots[1].powerUpId);

        int price = definition != nullptr ? definition->price : 0;

        targets.push_back(
            CreateShopItemTarget(1, SHOP_ANGLE_RIGHT, price)
        );
    }

    return targets;
}

inline void FillShopSlots(World& world, int slotCount = 2)
{
    auto& shop =
        world.GetResource<ShopResource>();

    auto& database =
        world.GetResource<PowerUpDatabaseResource>();

    shop.slots.clear();

    if(database.definitions.empty())
    {
        return;
    }

    for(int i = 0; i < slotCount; ++i)
    {
        int index =
            GetRandomValue(
                0,
                static_cast<int>(database.definitions.size()) - 1
            );

        ShopSlot slot{};
        slot.powerUpId = database.definitions[index].id;

        shop.slots.push_back(slot);
    }
}


inline void ReplaceShopSlot(World& world, int slotIndex)
{
    auto& shop =
        world.GetResource<ShopResource>();

    auto& database =
        world.GetResource<PowerUpDatabaseResource>();

    if(slotIndex < 0 ||
       slotIndex >= static_cast<int>(shop.slots.size()))
    {
        return;
    }

    if(database.definitions.empty())
    {
        return;
    }

    int index =
        GetRandomValue(
            0,
            static_cast<int>(database.definitions.size()) - 1
        );

    shop.slots[slotIndex].powerUpId =
        database.definitions[index].id;
}
