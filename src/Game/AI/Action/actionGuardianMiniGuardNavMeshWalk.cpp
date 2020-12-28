#include "Game/AI/Action/actionGuardianMiniGuardNavMeshWalk.h"

namespace uking::action {

GuardianMiniGuardNavMeshWalk::GuardianMiniGuardNavMeshWalk(const InitArg& arg) : NavMeshWalk(arg) {}

GuardianMiniGuardNavMeshWalk::~GuardianMiniGuardNavMeshWalk() = default;

void GuardianMiniGuardNavMeshWalk::loadParams_() {
    NavMeshAction::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::action
