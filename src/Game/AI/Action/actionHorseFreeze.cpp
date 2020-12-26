#include "Game/AI/Action/actionHorseFreeze.h"

namespace uking::action {

HorseFreeze::HorseFreeze(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

HorseFreeze::~HorseFreeze() = default;

bool HorseFreeze::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void HorseFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void HorseFreeze::leave_() {
    ActionWithPosAngReduce::leave_();
}

void HorseFreeze::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mPauseDelayFrames_s, "PauseDelayFrames");
    getStaticParam(&mCanRiddenWhenLeave_s, "CanRiddenWhenLeave");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mThrowOffAttackRigidBodyName_s, "ThrowOffAttackRigidBodyName");
    getDynamicParam(&mIsEnableThrowOffAttack_d, "IsEnableThrowOffAttack");
}

void HorseFreeze::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
