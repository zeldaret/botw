#include "Game/AI/Action/actionNPCAnchorWait.h"

namespace uking::action {

NPCAnchorWait::NPCAnchorWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCAnchorWait::~NPCAnchorWait() = default;

bool NPCAnchorWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCAnchorWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCAnchorWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCAnchorWait::loadParams_() {
    getDynamicParam(&mIsRainAnchor_d, "IsRainAnchor");
    getDynamicParam(&mIsStartSameAS_d, "IsStartSameAS");
    getDynamicParam(&mASName_d, "ASName");
}

void NPCAnchorWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
