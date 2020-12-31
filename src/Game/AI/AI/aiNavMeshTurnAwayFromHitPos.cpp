#include "Game/AI/AI/aiNavMeshTurnAwayFromHitPos.h"

namespace uking::ai {

NavMeshTurnAwayFromHitPos::NavMeshTurnAwayFromHitPos(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NavMeshTurnAwayFromHitPos::~NavMeshTurnAwayFromHitPos() = default;

bool NavMeshTurnAwayFromHitPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NavMeshTurnAwayFromHitPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NavMeshTurnAwayFromHitPos::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NavMeshTurnAwayFromHitPos::loadParams_() {
    getStaticParam(&mNumLOSCheckMax_s, "NumLOSCheckMax");
    getStaticParam(&mLOSCheckLength_s, "LOSCheckLength");
    getStaticParam(&mMoveToSafePosAfterTurn_s, "MoveToSafePosAfterTurn");
    getDynamicParam(&mHitPos_d, "HitPos");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
