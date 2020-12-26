#include "Game/AI/Action/actionSpinFlyAttack.h"

namespace uking::action {

SpinFlyAttack::SpinFlyAttack(const InitArg& arg) : LinearFlyAttack(arg) {}

SpinFlyAttack::~SpinFlyAttack() = default;

bool SpinFlyAttack::init_(sead::Heap* heap) {
    return LinearFlyAttack::init_(heap);
}

void SpinFlyAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    LinearFlyAttack::enter_(params);
}

void SpinFlyAttack::leave_() {
    LinearFlyAttack::leave_();
}

void SpinFlyAttack::loadParams_() {
    LinearFlyAttack::loadParams_();
    getStaticParam(&mRotSpeed_s, "RotSpeed");
}

void SpinFlyAttack::calc_() {
    LinearFlyAttack::calc_();
}

}  // namespace uking::action
