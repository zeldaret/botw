#include "Game/AI/AI/aiGameDataFlagSelector.h"

namespace uking::ai {

GameDataFlagSelector::GameDataFlagSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GameDataFlagSelector::~GameDataFlagSelector() = default;

bool GameDataFlagSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GameDataFlagSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GameDataFlagSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GameDataFlagSelector::loadParams_() {
    getStaticParam(&mCheckOnEnterOnly_s, "CheckOnEnterOnly");
    getMapUnitParam(&mClearFlag_m, "ClearFlag");
}

}  // namespace uking::ai
