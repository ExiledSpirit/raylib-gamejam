#include <raylib.h>
#include <unordered_map>
#include "TileMapResource.hpp"

struct TileDefinition
{
    char* name;
    Texture2D texture;
    bool solid;
    bool blocksLight;
};

struct TileDatabaseResource
{
    std::unordered_map<TileId, TileDefinition> definitions;
};
