#include "Game/Actor/Action/actionFollowAttack.h"

namespace uking::action {

FollowAttack::FollowAttack(const InitArg& arg) : ASPlayRotateTurnToTarget(arg) {}

FollowAttack::~FollowAttack() = default;

bool FollowAttack::init_(sead::Heap* heap) {
    return ASPlayRotateTurnToTarget::init_(heap);
}

void FollowAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ASPlayRotateTurnToTarget::enter_(params);
}

void FollowAttack::leave_() {
    ASPlayRotateTurnToTarget::leave_();
}

void FollowAttack::loadParams_() {
    ASPlayRotateTurnToTarget::loadParams_();
    getStaticParam(&mForceKillMode_s, "ForceKillMode");
    getStaticParam(&mIsRodDirHosei_s, "IsRodDirHosei");
}

void FollowAttack::calc_() {
    ASPlayRotateTurnToTarget::calc_();
}

}  // namespace uking::action
