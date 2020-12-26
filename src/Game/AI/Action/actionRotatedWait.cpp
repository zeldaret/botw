#include "Game/AI/Action/actionRotatedWait.h"

namespace uking::action {

RotatedWait::RotatedWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RotatedWait::~RotatedWait() = default;

bool RotatedWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RotatedWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RotatedWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void RotatedWait::loadParams_() {
    getMapUnitParam(&mRotAxis_m, "RotAxis");
    getMapUnitParam(&mTiltAngle_m, "TiltAngle");
}

void RotatedWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
