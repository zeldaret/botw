#include "Game/AI/Action/actionAttackBase.h"

namespace uking::action {

AttackBase::AttackBase(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

AttackBase::~AttackBase() = default;

bool AttackBase::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void AttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void AttackBase::leave_() {
    ActionWithPosAngReduce::leave_();
}

void AttackBase::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
}

void AttackBase::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
