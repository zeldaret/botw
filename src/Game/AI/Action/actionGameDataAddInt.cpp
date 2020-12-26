#include "Game/AI/Action/actionGameDataAddInt.h"

namespace uking::action {

GameDataAddInt::GameDataAddInt(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataAddInt::~GameDataAddInt() = default;

bool GameDataAddInt::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GameDataAddInt::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GameDataAddInt::leave_() {
    ksys::act::ai::Action::leave_();
}

void GameDataAddInt::loadParams_() {
    getDynamicParam(&mGameDataIntSrcName_d, "GameDataIntSrcName");
    getDynamicParam(&mGameDataIntDstName_d, "GameDataIntDstName");
    getDynamicParam(&mGameDataIntToName_d, "GameDataIntToName");
}

void GameDataAddInt::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
