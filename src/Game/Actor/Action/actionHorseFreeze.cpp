#include "Game/Actor/Action/actionHorseFreeze.h"

namespace uking::action {

HorseFreeze::HorseFreeze(const InitArg& arg) : StopBase(arg) {}

HorseFreeze::~HorseFreeze() = default;

bool HorseFreeze::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void HorseFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void HorseFreeze::leave_() {
    StopBase::leave_();
}

void HorseFreeze::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mPauseDelayFrames_s, "PauseDelayFrames");
    getStaticParam(&mCanRiddenWhenLeave_s, "CanRiddenWhenLeave");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mThrowOffAttackRigidBodyName_s, "ThrowOffAttackRigidBodyName");
    getDynamicParam(&mIsEnableThrowOffAttack_d, "IsEnableThrowOffAttack");
}

void HorseFreeze::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
