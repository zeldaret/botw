#include "Game/AI/Action/actionGameDataSubInt.h"

namespace uking::action {

GameDataSubInt::GameDataSubInt(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataSubInt::~GameDataSubInt() = default;

bool GameDataSubInt::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GameDataSubInt::loadParams_() {
    getDynamicParam(&mGameDataIntSrcName_d, "GameDataIntSrcName");
    getDynamicParam(&mGameDataIntDstName_d, "GameDataIntDstName");
    getDynamicParam(&mGameDataIntToName_d, "GameDataIntToName");
}

}  // namespace uking::action
