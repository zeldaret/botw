#include "Game/AI/Action/actionResetMasterSwordForceState.h"

namespace uking::action {

ResetMasterSwordForceState::ResetMasterSwordForceState(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ResetMasterSwordForceState::~ResetMasterSwordForceState() = default;

bool ResetMasterSwordForceState::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ResetMasterSwordForceState::loadParams_() {}

}  // namespace uking::action
