#include "Game/AI/Action/actionGameDataCopyInt.h"

namespace uking::action {

GameDataCopyInt::GameDataCopyInt(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataCopyInt::~GameDataCopyInt() = default;

bool GameDataCopyInt::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GameDataCopyInt::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GameDataCopyInt::leave_() {
    ksys::act::ai::Action::leave_();
}

void GameDataCopyInt::loadParams_() {
    getDynamicParam(&mGameDataIntSrcName_d, "GameDataIntSrcName");
    getDynamicParam(&mGameDataIntDstName_d, "GameDataIntDstName");
}

void GameDataCopyInt::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
