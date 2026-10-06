#include "Game/Actor/AI/aiNavMove.h"

namespace uking::ai {

NavMove::NavMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NavMove::~NavMove() = default;

bool NavMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NavMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NavMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NavMove::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mReachTargetArea_s, "ReachTargetArea");
    getStaticParam(&mTurnStartAng_s, "TurnStartAng");
}

}  // namespace uking::ai
