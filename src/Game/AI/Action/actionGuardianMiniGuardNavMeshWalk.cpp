#include "Game/AI/Action/actionGuardianMiniGuardNavMeshWalk.h"

namespace uking::action {

GuardianMiniGuardNavMeshWalk::GuardianMiniGuardNavMeshWalk(const InitArg& arg) : NavMeshWalk(arg) {}

GuardianMiniGuardNavMeshWalk::~GuardianMiniGuardNavMeshWalk() = default;

bool GuardianMiniGuardNavMeshWalk::init_(sead::Heap* heap) {
    return NavMeshWalk::init_(heap);
}

void GuardianMiniGuardNavMeshWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshWalk::enter_(params);
}

void GuardianMiniGuardNavMeshWalk::leave_() {
    NavMeshWalk::leave_();
}

void GuardianMiniGuardNavMeshWalk::loadParams_() {
    NavMeshAction::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mASName_s, "ASName");
}

void GuardianMiniGuardNavMeshWalk::calc_() {
    NavMeshWalk::calc_();
}

}  // namespace uking::action
