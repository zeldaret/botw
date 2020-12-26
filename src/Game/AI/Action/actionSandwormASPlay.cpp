#include "Game/AI/Action/actionSandwormASPlay.h"

namespace uking::action {

SandwormASPlay::SandwormASPlay(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

SandwormASPlay::~SandwormASPlay() = default;

bool SandwormASPlay::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void SandwormASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void SandwormASPlay::leave_() {
    ActionWithPosAngReduce::leave_();
}

void SandwormASPlay::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
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
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
