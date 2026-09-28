#include "Game/Actor/Action/actionNavMeshSlippedWalk.h"

namespace uking::action {

NavMeshSlippedWalk::NavMeshSlippedWalk(const InitArg& arg) : NavMeshMoveBase(arg) {}

NavMeshSlippedWalk::~NavMeshSlippedWalk() = default;

bool NavMeshSlippedWalk::init_(sead::Heap* heap) {
    return NavMeshMoveBase::init_(heap);
}

void NavMeshSlippedWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshMoveBase::enter_(params);
}

void NavMeshSlippedWalk::leave_() {
    NavMeshMoveBase::leave_();
}

void NavMeshSlippedWalk::loadParams_() {
    NavMeshMoveBase::loadParams_();
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mASName_s, "ASName");
}

void NavMeshSlippedWalk::calc_() {
    NavMeshMoveBase::calc_();
}

}  // namespace uking::action
