#include "Game/AI/Action/actionFollowAttack.h"

namespace uking::action {

FollowAttack::FollowAttack(const InitArg& arg) : RotateTurnToTarget(arg) {}

FollowAttack::~FollowAttack() = default;

bool FollowAttack::init_(sead::Heap* heap) {
    return RotateTurnToTarget::init_(heap);
}

void FollowAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    RotateTurnToTarget::enter_(params);
}

void FollowAttack::leave_() {
    RotateTurnToTarget::leave_();
}

void FollowAttack::loadParams_() {
    RotateTurnToTarget::loadParams_();
    getStaticParam(&mForceKillMode_s, "ForceKillMode");
    getStaticParam(&mIsRodDirHosei_s, "IsRodDirHosei");
}

void FollowAttack::calc_() {
    RotateTurnToTarget::calc_();
}

}  // namespace uking::action
