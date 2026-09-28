#include "Game/Actor/Action/actionFollowIgniteToBonePos.h"

namespace uking::action {

FollowIgniteToBonePos::FollowIgniteToBonePos(const InitArg& arg) : ASPlayRotateTurnToTarget(arg) {}

FollowIgniteToBonePos::~FollowIgniteToBonePos() = default;

bool FollowIgniteToBonePos::init_(sead::Heap* heap) {
    return ASPlayRotateTurnToTarget::init_(heap);
}

void FollowIgniteToBonePos::enter_(ksys::act::ai::InlineParamPack* params) {
    ASPlayRotateTurnToTarget::enter_(params);
}

void FollowIgniteToBonePos::leave_() {
    ASPlayRotateTurnToTarget::leave_();
}

void FollowIgniteToBonePos::loadParams_() {
    ASPlayRotateTurnToTarget::loadParams_();
    getStaticParam(&mLocalOffSetX_s, "LocalOffSetX");
    getStaticParam(&mLocalOffSetY_s, "LocalOffSetY");
    getStaticParam(&mLocalOffSetZ_s, "LocalOffSetZ");
    getStaticParam(&mIsIgnitePosYZero_s, "IsIgnitePosYZero");
    getStaticParam(&mBoneName_s, "BoneName");
}

void FollowIgniteToBonePos::calc_() {
    ASPlayRotateTurnToTarget::calc_();
}

}  // namespace uking::action
