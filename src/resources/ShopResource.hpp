#pragma once

#include <string>
#include <vector>

struct ShopSlot
{
    std::string powerUpId;
    bool sold = false;
};

struct ShopResource
{
    std::vector<ShopSlot> slots;

    int rerollCost = 1;
};
