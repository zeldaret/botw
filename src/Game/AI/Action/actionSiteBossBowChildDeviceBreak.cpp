#include "Game/AI/Action/actionSiteBossBowChildDeviceBreak.h"

namespace uking::action {

SiteBossBowChildDeviceBreak::SiteBossBowChildDeviceBreak(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossBowChildDeviceBreak::~SiteBossBowChildDeviceBreak() = default;

bool SiteBossBowChildDeviceBreak::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossBowChildDeviceBreak::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossBowChildDeviceBreak::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossBowChildDeviceBreak::loadParams_() {
    getStaticParam(&mReactionTime_s, "ReactionTime");
    getStaticParam(&mIsDelete_s, "IsDelete");
}

void SiteBossBowChildDeviceBreak::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
