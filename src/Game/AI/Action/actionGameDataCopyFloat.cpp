#include "Game/AI/Action/actionGameDataCopyFloat.h"

namespace uking::action {

GameDataCopyFloat::GameDataCopyFloat(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataCopyFloat::~GameDataCopyFloat() = default;

bool GameDataCopyFloat::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GameDataCopyFloat::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GameDataCopyFloat::leave_() {
    ksys::act::ai::Action::leave_();
}

void GameDataCopyFloat::loadParams_() {
    getDynamicParam(&mGameDataFloatSrcName_d, "GameDataFloatSrcName");
    getDynamicParam(&mGameDataFloatDstName_d, "GameDataFloatDstName");
}

void GameDataCopyFloat::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
