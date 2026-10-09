#include "Game/Actor/Action/actionStoppingAttackBase.h"

namespace uking::action {

StoppingAttackBase::StoppingAttackBase(const InitArg& arg) : StopBase(arg) {}

StoppingAttackBase::~StoppingAttackBase() = default;

bool StoppingAttackBase::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void StoppingAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void StoppingAttackBase::leave_() {
    StopBase::leave_();
}

void StoppingAttackBase::loadParams_() {
    StopBase::loadParams_();
}

void StoppingAttackBase::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
