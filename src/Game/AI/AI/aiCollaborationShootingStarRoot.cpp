#include "Game/AI/AI/aiCollaborationShootingStarRoot.h"

namespace uking::ai {

CollaborationShootingStarRoot::CollaborationShootingStarRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

CollaborationShootingStarRoot::~CollaborationShootingStarRoot() = default;

bool CollaborationShootingStarRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CollaborationShootingStarRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CollaborationShootingStarRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CollaborationShootingStarRoot::loadParams_() {
    getAITreeVariable(&mCollaboShootingStarId_a, "CollaboShootingStarId");
    // FIXME: CALL _ZN4sead14SafeStringBaseIcEaSERKS1_ @ 0x7100b0caa0
    // FIXME: CALL _ZNK4sead14SafeStringBaseIcE22assureTerminationImpl_Ev @ 0x89
    // FIXME: CALL _ZN4sead9HashCRC3214calcStringHashEPKc @ 0x7100b2170c
}

}  // namespace uking::ai
