#include "Game/AI/Action/actionStopCliffTongueAttack.h"

namespace uking::action {

StopCliffTongueAttack::StopCliffTongueAttack(const InitArg& arg) : OnCliffWait(arg) {}

StopCliffTongueAttack::~StopCliffTongueAttack() = default;

bool StopCliffTongueAttack::init_(sead::Heap* heap) {
    return OnCliffWait::init_(heap);
}

void StopCliffTongueAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    OnCliffWait::enter_(params);
}

void StopCliffTongueAttack::leave_() {
    OnCliffWait::leave_();
}

void StopCliffTongueAttack::loadParams_() {
    OnCliffWait::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mRigidName_s, "RigidName");
}

void StopCliffTongueAttack::calc_() {
    OnCliffWait::calc_();
}

}  // namespace uking::action
