#include "Game/AI/Action/actionGameDataAddFloat.h"

namespace uking::action {

GameDataAddFloat::GameDataAddFloat(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataAddFloat::~GameDataAddFloat() = default;

bool GameDataAddFloat::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GameDataAddFloat::loadParams_() {
    getDynamicParam(&mGameDataFloatSrcName_d, "GameDataFloatSrcName");
    getDynamicParam(&mGameDataFloatDstName_d, "GameDataFloatDstName");
    getDynamicParam(&mGameDataFloatToName_d, "GameDataFloatToName");
}

}  // namespace uking::action
