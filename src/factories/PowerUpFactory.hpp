#pragma once

#include "../resources/PowerUpDatabaseResource.hpp"

PowerUpDefinition CreateHeavyBatPowerUp();
PowerUpDefinition CreateLuckyGreatPowerUp();
PowerUpDefinition CreateExtraBallPowerUp();
void LoadCppPowerUps(PowerUpDatabaseResource& database);
