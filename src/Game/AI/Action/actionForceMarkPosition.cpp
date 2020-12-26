#include "Game/AI/Action/actionForceMarkPosition.h"

namespace uking::action {

ForceMarkPosition::ForceMarkPosition(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceMarkPosition::~ForceMarkPosition() = default;

bool ForceMarkPosition::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceMarkPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForceMarkPosition::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForceMarkPosition::loadParams_() {
    getDynamicParam(&mPinColorIdx_d, "PinColorIdx");
}

void ForceMarkPosition::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
