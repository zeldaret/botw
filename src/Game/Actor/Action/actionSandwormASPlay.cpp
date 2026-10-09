#include "Game/Actor/Action/actionSandwormASPlay.h"

namespace uking::action {

SandwormASPlay::SandwormASPlay(const InitArg& arg) : StopBase(arg) {}

SandwormASPlay::~SandwormASPlay() = default;

bool SandwormASPlay::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void SandwormASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void SandwormASPlay::leave_() {
    StopBase::leave_();
}

void SandwormASPlay::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mChangeOffsetDelay_s, "ChangeOffsetDelay");
    getStaticParam(&mTargetSandOffset_s, "TargetSandOffset");
    getStaticParam(&mSandOffsetSpeed_s, "SandOffsetSpeed");
    getStaticParam(&mWaitASFinish_s, "WaitASFinish");
    getStaticParam(&mWaitSandOffset_s, "WaitSandOffset");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsUseAtEvent_s, "IsUseAtEvent");
    getStaticParam(&mIsUseTossAt_s, "IsUseTossAt");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mTransBoneName_s, "TransBoneName");
}

void SandwormASPlay::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
