#include "Game/AI/Action/actionNullASPlay.h"

namespace uking::action {

NullASPlay::NullASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NullASPlay::~NullASPlay() = default;

bool NullASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NullASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NullASPlay::leave_() {
    ksys::act::ai::Action::leave_();
}

void NullASPlay::loadParams_() {
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
}

void NullASPlay::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
