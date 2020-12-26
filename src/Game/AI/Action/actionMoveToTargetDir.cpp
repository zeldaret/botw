#include "Game/AI/Action/actionMoveToTargetDir.h"

namespace uking::action {

MoveToTargetDir::MoveToTargetDir(const InitArg& arg) : MoveToTargetBase(arg) {}

MoveToTargetDir::~MoveToTargetDir() = default;

bool MoveToTargetDir::init_(sead::Heap* heap) {
    return MoveToTargetBase::init_(heap);
}

void MoveToTargetDir::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveToTargetBase::enter_(params);
}

void MoveToTargetDir::leave_() {
    MoveToTargetBase::leave_();
}

void MoveToTargetDir::loadParams_() {
    MoveToTargetBase::loadParams_();
    getDynamicParam(&mFrontDir_d, "FrontDir");
    getDynamicParam(&mDynTargetPos_d, "DynTargetPos");
    getDynamicParam(&mDynStartPos_d, "DynStartPos");
    getMapUnitParam(&mRailMoveSpeed_m, "RailMoveSpeed");
}

void MoveToTargetDir::calc_() {
    MoveToTargetBase::calc_();
}

}  // namespace uking::action
