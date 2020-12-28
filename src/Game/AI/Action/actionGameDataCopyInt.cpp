#include "Game/AI/Action/actionGameDataCopyInt.h"

namespace uking::action {

GameDataCopyInt::GameDataCopyInt(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataCopyInt::~GameDataCopyInt() = default;

bool GameDataCopyInt::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GameDataCopyInt::loadParams_() {
    getDynamicParam(&mGameDataIntSrcName_d, "GameDataIntSrcName");
    getDynamicParam(&mGameDataIntDstName_d, "GameDataIntDstName");
}

}  // namespace uking::action
