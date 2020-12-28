#include "Game/AI/Action/actionGameDataAddInt.h"

namespace uking::action {

GameDataAddInt::GameDataAddInt(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataAddInt::~GameDataAddInt() = default;

bool GameDataAddInt::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GameDataAddInt::loadParams_() {
    getDynamicParam(&mGameDataIntSrcName_d, "GameDataIntSrcName");
    getDynamicParam(&mGameDataIntDstName_d, "GameDataIntDstName");
    getDynamicParam(&mGameDataIntToName_d, "GameDataIntToName");
}

}  // namespace uking::action
