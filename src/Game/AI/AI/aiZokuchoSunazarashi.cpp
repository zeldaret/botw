#include "Game/AI/AI/aiZokuchoSunazarashi.h"

namespace uking::ai {

ZokuchoSunazarashi::ZokuchoSunazarashi(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ZokuchoSunazarashi::~ZokuchoSunazarashi() = default;

bool ZokuchoSunazarashi::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ZokuchoSunazarashi::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ZokuchoSunazarashi::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ZokuchoSunazarashi::loadParams_() {
    getStaticParam(&mPlayerLostDis_s, "PlayerLostDis");
    getStaticParam(&mLeadPlayerAngle_s, "LeadPlayerAngle");
    getStaticParam(&mMoveTargetDist_s, "MoveTargetDist");
    getStaticParam(&mStopMoveDist_s, "StopMoveDist");
    getStaticParam(&mStayAwayDist_s, "StayAwayDist");
}

}  // namespace uking::ai
