#include "Game/AI/AI/aiDeadOrOtherState.h"

namespace uking::ai {

DeadOrOtherState::DeadOrOtherState(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool DeadOrOtherState::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DeadOrOtherState::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DeadOrOtherState::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DeadOrOtherState::loadParams_() {}

}  // namespace uking::ai
