#include "Game/AI/Action/actionNavMeshSlippedWalk.h"

namespace uking::action {

NavMeshSlippedWalk::NavMeshSlippedWalk(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshSlippedWalk::~NavMeshSlippedWalk() = default;

bool NavMeshSlippedWalk::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshSlippedWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
}

void NavMeshSlippedWalk::leave_() {
    NavMeshAction::leave_();
}

void NavMeshSlippedWalk::loadParams_() {
    NavMeshAction::loadParams_();
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mASName_s, "ASName");
}

void NavMeshSlippedWalk::calc_() {
    NavMeshAction::calc_();
}

}  // namespace uking::action
