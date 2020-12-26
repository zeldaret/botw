#include "Game/AI/Action/actionSetFrameASPlay.h"

namespace uking::action {

SetFrameASPlay::SetFrameASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetFrameASPlay::~SetFrameASPlay() = default;

bool SetFrameASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetFrameASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetFrameASPlay::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetFrameASPlay::loadParams_() {
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
    getMapUnitParam(&mASFrame_m, "ASFrame");
}

void SetFrameASPlay::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
