#include "Game/AI/AI/aiSetTargetPosToPlayer.h"

namespace uking::ai {

SetTargetPosToPlayer::SetTargetPosToPlayer(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SetTargetPosToPlayer::~SetTargetPosToPlayer() = default;

bool SetTargetPosToPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SetTargetPosToPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SetTargetPosToPlayer::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SetTargetPosToPlayer::loadParams_() {
    getStaticParam(&mUpdateTargetInterval_s, "UpdateTargetInterval");
    getStaticParam(&mMaxUpdateNum_s, "MaxUpdateNum");
    getStaticParam(&mAddLength_s, "AddLength");
    getStaticParam(&mHeightOffset_s, "HeightOffset");
    getStaticParam(&mRandRange_s, "RandRange");
    getStaticParam(&mRandRate_s, "RandRate");
}

}  // namespace uking::ai
