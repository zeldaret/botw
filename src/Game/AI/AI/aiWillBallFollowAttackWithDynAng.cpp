#include "Game/AI/AI/aiWillBallFollowAttackWithDynAng.h"

namespace uking::ai {

WillBallFollowAttackWithDynAng::WillBallFollowAttackWithDynAng(const InitArg& arg)
    : WillBallFollowAttack(arg) {}

WillBallFollowAttackWithDynAng::~WillBallFollowAttackWithDynAng() = default;

bool WillBallFollowAttackWithDynAng::init_(sead::Heap* heap) {
    return WillBallFollowAttack::init_(heap);
}

void WillBallFollowAttackWithDynAng::enter_(ksys::act::ai::InlineParamPack* params) {
    WillBallFollowAttack::enter_(params);
}

void WillBallFollowAttackWithDynAng::leave_() {
    WillBallFollowAttack::leave_();
}

void WillBallFollowAttackWithDynAng::loadParams_() {
    WillBallFollowAttack::loadParams_();
    getDynamicParam(&mAngle_d, "Angle");
}

}  // namespace uking::ai
