#include "Game/AI/Action/actionGameDataSubVec3.h"

namespace uking::action {

GameDataSubVec3::GameDataSubVec3(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataSubVec3::~GameDataSubVec3() = default;

bool GameDataSubVec3::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GameDataSubVec3::loadParams_() {
    getDynamicParam(&mGameDataVec3fSrcName_d, "GameDataVec3fSrcName");
    getDynamicParam(&mGameDataVec3fDstName_d, "GameDataVec3fDstName");
    getDynamicParam(&mGameDataVec3fToName_d, "GameDataVec3fToName");
}

}  // namespace uking::action
