#include "Game/AI/Action/actionForkEndByDistance.h"

namespace uking::action {

ForkEndByDistance::ForkEndByDistance(const InitArg& arg) : Fork(arg) {}

ForkEndByDistance::~ForkEndByDistance() = default;

bool ForkEndByDistance::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkEndByDistance::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkEndByDistance::leave_() {
    Fork::leave_();
}

void ForkEndByDistance::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mEndMode_s, "EndMode");
    getStaticParam(&mEndDist_s, "EndDist");
    getStaticParam(&mIsOnlyXZ_s, "IsOnlyXZ");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkEndByDistance::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
