#include "Game/AI/Action/actionOff.h"

namespace uking::action {

Off::Off(const InitArg& arg) : ActionEx(arg) {}

Off::~Off() = default;

bool Off::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void Off::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void Off::leave_() {
    ActionEx::leave_();
}

void Off::loadParams_() {
    getStaticParam(&mLinkTagType_s, "LinkTagType");
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mOffWaitRevival_s, "OffWaitRevival");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
}

void Off::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
