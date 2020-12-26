#include "Game/AI/Action/actionGanonChangeState.h"

namespace uking::action {

GanonChangeState::GanonChangeState(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonChangeState::~GanonChangeState() = default;

bool GanonChangeState::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonChangeState::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GanonChangeState::leave_() {
    ksys::act::ai::Action::leave_();
}

void GanonChangeState::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GanonChangeState::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
