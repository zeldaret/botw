#include "Game/AI/AI/aiGuardianMiniOnNoNavMesh.h"

namespace uking::ai {

GuardianMiniOnNoNavMesh::GuardianMiniOnNoNavMesh(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianMiniOnNoNavMesh::~GuardianMiniOnNoNavMesh() = default;

void GuardianMiniOnNoNavMesh::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianMiniOnNoNavMesh::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniOnNoNavMesh::loadParams_() {
    getStaticParam(&mChangeToIceTimer_s, "ChangeToIceTimer");
}

}  // namespace uking::ai
