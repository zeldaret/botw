#include "Game/AI/AI/aiHiddenOctarockSearchTarget.h"

namespace uking::ai {

HiddenOctarockSearchTarget::HiddenOctarockSearchTarget(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

HiddenOctarockSearchTarget::~HiddenOctarockSearchTarget() = default;

bool HiddenOctarockSearchTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HiddenOctarockSearchTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HiddenOctarockSearchTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HiddenOctarockSearchTarget::loadParams_() {
    getStaticParam(&mNoticeTerrorLevel_s, "NoticeTerrorLevel");
    getStaticParam(&mNoticeWorryRange_s, "NoticeWorryRange");
}

}  // namespace uking::ai
