#include "Game/AI/Action/actionResetMasterSwordForceState.h"

namespace uking::action {

ResetMasterSwordForceState::ResetMasterSwordForceState(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ResetMasterSwordForceState::~ResetMasterSwordForceState() = default;

bool ResetMasterSwordForceState::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ResetMasterSwordForceState::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ResetMasterSwordForceState::leave_() {
    ksys::act::ai::Action::leave_();
}

void ResetMasterSwordForceState::loadParams_() {}

void ResetMasterSwordForceState::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
