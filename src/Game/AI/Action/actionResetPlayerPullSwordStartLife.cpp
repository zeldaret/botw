#include "Game/AI/Action/actionResetPlayerPullSwordStartLife.h"

namespace uking::action {

ResetPlayerPullSwordStartLife::ResetPlayerPullSwordStartLife(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ResetPlayerPullSwordStartLife::~ResetPlayerPullSwordStartLife() = default;

bool ResetPlayerPullSwordStartLife::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ResetPlayerPullSwordStartLife::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ResetPlayerPullSwordStartLife::leave_() {
    ksys::act::ai::Action::leave_();
}

void ResetPlayerPullSwordStartLife::loadParams_() {}

void ResetPlayerPullSwordStartLife::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
