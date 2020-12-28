#include "Game/AI/Action/actionGameDataSubFloat.h"

namespace uking::action {

GameDataSubFloat::GameDataSubFloat(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataSubFloat::~GameDataSubFloat() = default;

bool GameDataSubFloat::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GameDataSubFloat::loadParams_() {
    getDynamicParam(&mGameDataFloatSrcName_d, "GameDataFloatSrcName");
    getDynamicParam(&mGameDataFloatDstName_d, "GameDataFloatDstName");
    getDynamicParam(&mGameDataFloatToName_d, "GameDataFloatToName");
}

}  // namespace uking::action
