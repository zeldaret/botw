#include "Game/AI/Action/actionLinearFlyAttack.h"

namespace uking::action {

LinearFlyAttack::LinearFlyAttack(const InitArg& arg) : LinearFlyAttackBase(arg) {}

bool LinearFlyAttack::init_(sead::Heap* heap) {
    return LinearFlyAttackBase::init_(heap);
}

void LinearFlyAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    LinearFlyAttackBase::enter_(params);
}

void LinearFlyAttack::leave_() {
    LinearFlyAttackBase::leave_();
}

void LinearFlyAttack::loadParams_() {
    LinearFlyAttackBase::loadParams_();
}

void LinearFlyAttack::calc_() {
    LinearFlyAttackBase::calc_();
}

}  // namespace uking::action
