#include "Game/Actor/Action/actionHorseElectricParalysis.h"

namespace uking::action {

HorseElectricParalysis::HorseElectricParalysis(const InitArg& arg) : StopBase(arg) {}

HorseElectricParalysis::~HorseElectricParalysis() = default;

bool HorseElectricParalysis::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void HorseElectricParalysis::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void HorseElectricParalysis::leave_() {
    StopBase::leave_();
}

void HorseElectricParalysis::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mPauseDelayFrames_s, "PauseDelayFrames");
    getStaticParam(&mCanRiddenWhenLeave_s, "CanRiddenWhenLeave");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mThrowOffAttackRigidBodyName_s, "ThrowOffAttackRigidBodyName");
    getDynamicParam(&mIsEnableThrowOffAttack_d, "IsEnableThrowOffAttack");
}

void HorseElectricParalysis::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
