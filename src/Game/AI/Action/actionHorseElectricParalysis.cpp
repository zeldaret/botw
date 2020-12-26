#include "Game/AI/Action/actionHorseElectricParalysis.h"

namespace uking::action {

HorseElectricParalysis::HorseElectricParalysis(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

HorseElectricParalysis::~HorseElectricParalysis() = default;

bool HorseElectricParalysis::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void HorseElectricParalysis::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void HorseElectricParalysis::leave_() {
    ActionWithPosAngReduce::leave_();
}

void HorseElectricParalysis::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mPauseDelayFrames_s, "PauseDelayFrames");
    getStaticParam(&mCanRiddenWhenLeave_s, "CanRiddenWhenLeave");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mThrowOffAttackRigidBodyName_s, "ThrowOffAttackRigidBodyName");
    getDynamicParam(&mIsEnableThrowOffAttack_d, "IsEnableThrowOffAttack");
}

void HorseElectricParalysis::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
