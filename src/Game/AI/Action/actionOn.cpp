#include "Game/AI/Action/actionOn.h"

namespace uking::action {

On::On(const InitArg& arg) : ActionEx(arg) {}

On::~On() = default;

bool On::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void On::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void On::leave_() {
    ActionEx::leave_();
}

void On::loadParams_() {
    getStaticParam(&mLinkTagType_s, "LinkTagType");
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mOnWaitRevival_s, "OnWaitRevival");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
}

void On::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
