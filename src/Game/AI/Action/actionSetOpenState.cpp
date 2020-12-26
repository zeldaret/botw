#include "Game/AI/Action/actionSetOpenState.h"

namespace uking::action {

SetOpenState::SetOpenState(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetOpenState::~SetOpenState() = default;

bool SetOpenState::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetOpenState::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetOpenState::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetOpenState::loadParams_() {
    getAITreeVariable(&mIsOpenTreasureBox_a, "IsOpenTreasureBox");
}

void SetOpenState::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
