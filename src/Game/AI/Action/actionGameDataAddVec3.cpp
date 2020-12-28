#include "Game/AI/Action/actionGameDataAddVec3.h"

namespace uking::action {

GameDataAddVec3::GameDataAddVec3(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataAddVec3::~GameDataAddVec3() = default;

bool GameDataAddVec3::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GameDataAddVec3::loadParams_() {
    getDynamicParam(&mGameDataVec3fSrcName_d, "GameDataVec3fSrcName");
    getDynamicParam(&mGameDataVec3fDstName_d, "GameDataVec3fDstName");
    getDynamicParam(&mGameDataVec3fToName_d, "GameDataVec3fToName");
}

}  // namespace uking::action
