#include "Game/AI/Action/actionGameDataCopyFloat.h"

namespace uking::action {

GameDataCopyFloat::GameDataCopyFloat(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataCopyFloat::~GameDataCopyFloat() = default;

bool GameDataCopyFloat::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GameDataCopyFloat::loadParams_() {
    getDynamicParam(&mGameDataFloatSrcName_d, "GameDataFloatSrcName");
    getDynamicParam(&mGameDataFloatDstName_d, "GameDataFloatDstName");
}

}  // namespace uking::action
