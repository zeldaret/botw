#include "Game/Actor/Action/actionNavMeshLiftWalk.h"

namespace uking::action {

NavMeshLiftWalk::NavMeshLiftWalk(const InitArg& arg) : NavMeshMoveBase(arg) {}

bool NavMeshLiftWalk::init_(sead::Heap* heap) {
    return NavMeshMoveBase::init_(heap);
}

void NavMeshLiftWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshMoveBase::enter_(params);
}

void NavMeshLiftWalk::leave_() {
    NavMeshMoveBase::leave_();
}

void NavMeshLiftWalk::loadParams_() {
    NavMeshMoveBase::loadParams_();
}

void NavMeshLiftWalk::calc_() {
    NavMeshMoveBase::calc_();
}

}  // namespace uking::action
