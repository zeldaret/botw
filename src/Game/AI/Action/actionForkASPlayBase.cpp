#include "Game/AI/Action/actionForkASPlayBase.h"

namespace uking::action {

ForkASPlayBase::ForkASPlayBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASPlayBase::~ForkASPlayBase() = default;

bool ForkASPlayBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASPlayBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkASPlayBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASPlayBase::loadParams_() {
    getStaticParam(&mEndState_s, "EndState");
    getStaticParam(&mChangeableTiming_s, "ChangeableTiming");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mFirstRandomRatio_s, "FirstRandomRatio");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
}

void ForkASPlayBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
