#include "Game/AI/AI/aiFriendCallAction.h"

namespace uking::ai {

FriendCallAction::FriendCallAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FriendCallAction::~FriendCallAction() = default;

bool FriendCallAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FriendCallAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void FriendCallAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FriendCallAction::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mNearDistH_s, "NearDistH");
    getStaticParam(&mNearDistVMax_s, "NearDistVMax");
    getStaticParam(&mNearDistVMin_s, "NearDistVMin");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
