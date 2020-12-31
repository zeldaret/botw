#include "Game/AI/AI/aiSiteBossApproachRoot.h"

namespace uking::ai {

SiteBossApproachRoot::SiteBossApproachRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossApproachRoot::~SiteBossApproachRoot() = default;

bool SiteBossApproachRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossApproachRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossApproachRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossApproachRoot::loadParams_() {
    getStaticParam(&mCheckWallDist_s, "CheckWallDist");
    getStaticParam(&mApproachTime_s, "ApproachTime");
    getStaticParam(&mEndDist_s, "EndDist");
    getStaticParam(&mEndFarDist_s, "EndFarDist");
    getStaticParam(&mAttackStartDist_s, "AttackStartDist");
    getStaticParam(&mDoAttack_s, "DoAttack");
    getDynamicParam(&mIsMoveSide_d, "IsMoveSide");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
