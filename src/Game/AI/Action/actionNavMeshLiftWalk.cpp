#include "Game/AI/Action/actionNavMeshLiftWalk.h"

namespace uking::action {

NavMeshLiftWalk::NavMeshLiftWalk(const InitArg& arg) : NavMeshAction(arg) {}

bool NavMeshLiftWalk::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshLiftWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
}

void NavMeshLiftWalk::leave_() {
    NavMeshAction::leave_();
}

void NavMeshLiftWalk::loadParams_() {
    NavMeshAction::loadParams_();
}

void NavMeshLiftWalk::calc_() {
    NavMeshAction::calc_();
}

}  // namespace uking::action
