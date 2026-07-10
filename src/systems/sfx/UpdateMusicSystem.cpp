#include "UpdateMusicSystem.hpp"
#include "../../utils/AudioHelper.hpp"

void UpdateMusicSystem(World& world) {
    AudioHelper::Update();
}
