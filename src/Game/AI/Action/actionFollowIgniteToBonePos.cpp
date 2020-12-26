#include "Game/AI/Action/actionFollowIgniteToBonePos.h"

namespace uking::action {

FollowIgniteToBonePos::FollowIgniteToBonePos(const InitArg& arg) : RotateTurnToTarget(arg) {}

FollowIgniteToBonePos::~FollowIgniteToBonePos() = default;

bool FollowIgniteToBonePos::init_(sead::Heap* heap) {
    return RotateTurnToTarget::init_(heap);
}

void FollowIgniteToBonePos::enter_(ksys::act::ai::InlineParamPack* params) {
    RotateTurnToTarget::enter_(params);
}

void FollowIgniteToBonePos::leave_() {
    RotateTurnToTarget::leave_();
}

void FollowIgniteToBonePos::loadParams_() {
    RotateTurnToTarget::loadParams_();
    getStaticParam(&mLocalOffSetX_s, "LocalOffSetX");
    getStaticParam(&mLocalOffSetY_s, "LocalOffSetY");
    getStaticParam(&mLocalOffSetZ_s, "LocalOffSetZ");
    getStaticParam(&mIsIgnitePosYZero_s, "IsIgnitePosYZero");
    getStaticParam(&mBoneName_s, "BoneName");
}

void FollowIgniteToBonePos::calc_() {
    RotateTurnToTarget::calc_();
}

}  // namespace uking::action
