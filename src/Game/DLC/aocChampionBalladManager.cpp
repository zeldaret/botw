#include "Game/DLC/aocChampionBalladManager.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(ChampionBalladManager)

void ChampionBalladManager::init() {
    mBlightCounts = {};
}

void ChampionBalladManager::setBlightRematchCount(s8 count, BlightType blight_type) {
    if (count >= 0 && blight_type <= BlightType::Water) {
        if (count >= 30) {
            count = 30;
        }
        mBlightCounts[u32(blight_type)] = count;
    }
}

void ChampionBalladManager::incrementBlightRematchCount(BlightType blight_type) {
    if (blight_type <= BlightType::Water) {
        s8 count = mBlightCounts[u32(blight_type)] + 1;
        setBlightRematchCount(count, blight_type);
    }
}

s8 ChampionBalladManager::getBlightRematchCount(BlightType blight_type) const {
    if (blight_type <= BlightType::Water)
        return mBlightCounts[u32(blight_type)];
    return 0;
}
}  // namespace uking
