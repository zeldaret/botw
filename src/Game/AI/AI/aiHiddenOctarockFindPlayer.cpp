#include "Game/AI/AI/aiHiddenOctarockFindPlayer.h"

namespace uking::ai {

HiddenOctarockFindPlayer::HiddenOctarockFindPlayer(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HiddenOctarockFindPlayer::~HiddenOctarockFindPlayer() = default;

bool HiddenOctarockFindPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HiddenOctarockFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HiddenOctarockFindPlayer::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HiddenOctarockFindPlayer::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mActorRadius_s, "ActorRadius");
    getStaticParam(&mLostDistOffset_s, "LostDistOffset");
    getStaticParam(&mNoticeDelayTime_s, "NoticeDelayTime");
}

}  // namespace uking::ai
