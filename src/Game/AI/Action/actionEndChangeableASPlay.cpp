#include "Game/AI/Action/actionEndChangeableASPlay.h"

namespace uking::action {

EndChangeableASPlay::EndChangeableASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EndChangeableASPlay::~EndChangeableASPlay() = default;

bool EndChangeableASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EndChangeableASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EndChangeableASPlay::leave_() {
    ksys::act::ai::Action::leave_();
}

void EndChangeableASPlay::loadParams_() {
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
}

void EndChangeableASPlay::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
