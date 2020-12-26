#include "Game/AI/Action/actionMoveByAnimeDrivenToTarget.h"

namespace uking::action {

MoveByAnimeDrivenToTarget::MoveByAnimeDrivenToTarget(const InitArg& arg) : MoveByAnimeDriven(arg) {}

MoveByAnimeDrivenToTarget::~MoveByAnimeDrivenToTarget() = default;

bool MoveByAnimeDrivenToTarget::init_(sead::Heap* heap) {
    return MoveByAnimeDriven::init_(heap);
}

void MoveByAnimeDrivenToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveByAnimeDriven::enter_(params);
}

void MoveByAnimeDrivenToTarget::leave_() {
    MoveByAnimeDriven::leave_();
}

void MoveByAnimeDrivenToTarget::loadParams_() {
    MoveByAnimeDriven::loadParams_();
    getStaticParam(&mAnimRotateMax_s, "AnimRotateMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void MoveByAnimeDrivenToTarget::calc_() {
    MoveByAnimeDriven::calc_();
}

}  // namespace uking::action
