#include "Game/AI/Action/actionGameDataSubFloat.h"

namespace uking::action {

GameDataSubFloat::GameDataSubFloat(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataSubFloat::~GameDataSubFloat() = default;

bool GameDataSubFloat::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GameDataSubFloat::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GameDataSubFloat::leave_() {
    ksys::act::ai::Action::leave_();
}

void GameDataSubFloat::loadParams_() {
    getDynamicParam(&mGameDataFloatSrcName_d, "GameDataFloatSrcName");
    getDynamicParam(&mGameDataFloatDstName_d, "GameDataFloatDstName");
    getDynamicParam(&mGameDataFloatToName_d, "GameDataFloatToName");
}

void GameDataSubFloat::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
