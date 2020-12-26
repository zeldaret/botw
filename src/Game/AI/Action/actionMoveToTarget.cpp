#include "Game/AI/Action/actionMoveToTarget.h"

namespace uking::action {

MoveToTarget::MoveToTarget(const InitArg& arg) : MoveToTargetBase(arg) {}

MoveToTarget::~MoveToTarget() = default;

bool MoveToTarget::init_(sead::Heap* heap) {
    return MoveToTargetBase::init_(heap);
}

void MoveToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveToTargetBase::enter_(params);
}

void MoveToTarget::leave_() {
    MoveToTargetBase::leave_();
}

void MoveToTarget::loadParams_() {
    MoveToTargetBase::loadParams_();
    getMapUnitParam(&mRailMoveSpeed_m, "RailMoveSpeed");
}

void MoveToTarget::calc_() {
    MoveToTargetBase::calc_();
}

}  // namespace uking::action
