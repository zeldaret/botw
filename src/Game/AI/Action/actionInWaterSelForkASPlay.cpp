#include "Game/AI/Action/actionInWaterSelForkASPlay.h"

namespace uking::action {

InWaterSelForkASPlay::InWaterSelForkASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

InWaterSelForkASPlay::~InWaterSelForkASPlay() = default;

bool InWaterSelForkASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void InWaterSelForkASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void InWaterSelForkASPlay::leave_() {
    ksys::act::ai::Action::leave_();
}

void InWaterSelForkASPlay::loadParams_() {
    getStaticParam(&mEndState_s, "EndState");
    getStaticParam(&mChangeableTiming_s, "ChangeableTiming");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mFirstRandomRatio_s, "FirstRandomRatio");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
}

void InWaterSelForkASPlay::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
